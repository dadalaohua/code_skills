#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef enum
{
    LRC_TAG_ID_AL = 0,  //专辑名
    LRC_TAG_ID_AR,      //歌手名
    LRC_TAG_ID_AU,      //歌词作者-作曲家
    LRC_TAG_ID_BY,      //此LRC文件的创建者
    LRC_TAG_ID_OFFSET,  //+/- 时间补偿值，以毫秒为单位，正值表示加快，负值表示延后
    LRC_TAG_ID_RE,      //创建此LRC文件的播放器或编辑器
    LRC_TAG_ID_TI,      //歌词(歌曲)的标题
    LRC_TAG_ID_VE,      //程序的版本
    LRC_TAG_ID_MAX,
} lrc_tag_id_e;

static char *idtags[] = {
    "[al:",
    "[ar:",
    "[au:",
    "[by:",
    "[re:",
    "[ti:",
    "[ve:",
    "[offset:",
};


#define LRC_LYRIC_SAME_TIME_CAPACITY    2
#define LRC_LYRIC_CAPACITY              256
#define LRC_LYRIC_MAX_LEN               1024

typedef struct
{
    int time;
    char **lyric;
    int capacity;
    int cnt;
} lrc_lyric_t;

typedef struct
{
    int len;
    lrc_lyric_t* lyrics;
    int lyric_len;
    
    char* id_tag[LRC_TAG_ID_MAX];
} lrc_t;

static lrc_t lrc_info = {0};

int compare(const void* a, const void* b) 
{
    return ((lrc_lyric_t*)a)->time - ((lrc_lyric_t*)b)->time;
}

/**
  * @brief      释放内存
  *
  * @return     无
  */
void lrc_free(void)
{
    if(lrc_info.len && lrc_info.lyrics) {
        for(int i = 0; i < lrc_info.lyric_len; i++) {
            if(lrc_info.lyrics[i].lyric) {
                for(int j = 0; j < lrc_info.lyrics[i].cnt; j++) {
                    if(lrc_info.lyrics[i].lyric[j])
                        free(lrc_info.lyrics[i].lyric[j]);
                }
                free(lrc_info.lyrics[i].lyric);
            }
        }
        lrc_info.len = 0;
        free(lrc_info.lyrics);
        lrc_info.lyrics = NULL;
        lrc_info.lyric_len = 0;
    }
    
    for(int i = 0; i < LRC_TAG_ID_MAX; i++) {
        if(lrc_info.id_tag[i]) {
            free(lrc_info.id_tag[i]);
            lrc_info.id_tag[i] = NULL;
        }
    }
}

/**
  * @brief      LRC格式解析
  * @param[in]  filename : 文件名
  *
  * @return     无
  */
int lrc_parse(char *filename)
{
    FILE *fp;
    char buf[LRC_LYRIC_MAX_LEN] = {0};
    int mtime, stime, mstime;
    //打开文件
    if((fp = fopen(filename, "r")) == NULL) {
        printf("open file %s failed!\n", filename);
        goto err0;
    }
    fseek(fp, 0, SEEK_SET);
    
    //释放上次使用的内存
    lrc_free();
    
    //预申请空间
    lrc_info.len = LRC_LYRIC_CAPACITY;
    lrc_info.lyrics = malloc(sizeof(char *) * lrc_info.len);
    if(lrc_info.lyrics == NULL) {
        goto err1;
    }
    
    int cnt = 0;
    
    //读取文件内容
    while(fgets(buf, LRC_LYRIC_MAX_LEN, fp) != NULL) {
        int len = strlen(buf);
        if(len > 6 && (buf[1] >= '0' && buf[1] <= '9') && (buf[2] >= '0' && buf[2] <= '9')) {
            int bufstart = 0;
            int buflen = 0;
            for(int i = 0; i < len; i++) {
                if(buf[i] == ']' && buf[i + 1] != '[') {
                    buflen = strlen(&buf[i + 1]);
                    bufstart = i + 1;
                }
            }
            
            for(int i = 0; i < bufstart; i++) {
                if((buf[i] == '[') && (buf[i + 1] >= '0' && buf[i + 1] <= '9') && (buf[i + 2] >= '0' && buf[i + 2] <= '9')) {
                    
                    if(buf[i + 6] == ']') {
                        sscanf(&buf[i], "[%d:%d]", &mtime, &stime);
                        mstime = 0;
                    } else {
                        sscanf(&buf[i], "[%d:%d.%d]", &mtime, &stime, &mstime);
                        
                        if(buf[i + 9] == ']') {
                            mstime *= 10;
                        }
                    }
                    
                    int time = (mtime * 60 + stime) * 1000 + mstime;
                    int id = cnt;
                    int id_len = 0;
                    for(int j = 0; j < cnt; j++) {
                        if(lrc_info.lyrics[j].time == time) {
                            id = j;
                            id_len = lrc_info.lyrics[j].cnt;
                            if(id_len >= lrc_info.lyrics[id].capacity) {
                                lrc_info.lyrics[id].capacity <<= 1;
                                void* tmp_ptr = lrc_info.lyrics[id].lyric;
                                lrc_info.lyrics[id].lyric = realloc(lrc_info.lyrics[id].lyric, sizeof(char *) * lrc_info.lyrics[id].capacity);
                                if(lrc_info.lyrics[id].lyric == NULL) {
                                    free(tmp_ptr);
                                    goto err2;
                                }
                            }
                            break;
                        }
                    }
                    
                    if(id == cnt) {
                        lrc_info.lyrics[id].time = time;
                        lrc_info.lyrics[id].capacity = LRC_LYRIC_SAME_TIME_CAPACITY;
                        lrc_info.lyrics[id].lyric = malloc(sizeof(char *) * lrc_info.lyrics[id].capacity);
                        lrc_info.lyrics[id].cnt = 0;
                        
                        if(lrc_info.lyrics[id].lyric == NULL) {
                            goto err2;
                        }
                    }
                    
                    lrc_info.lyrics[id].lyric[id_len] = malloc(sizeof(char) * (buflen + 1));
                    if(lrc_info.lyrics[id].lyric[id_len] == NULL) {
                        goto err2;
                    }
                    strcpy(lrc_info.lyrics[id].lyric[id_len], &buf[bufstart]);
                    lrc_info.lyrics[id].cnt++;
                    
                    if(id == cnt) {
                        cnt++;
                        if(cnt >= lrc_info.len) {
                            lrc_info.len <<= 1;
                            void* tmp_ptr = lrc_info.lyrics;
                            lrc_info.lyrics = realloc(lrc_info.lyrics, sizeof(char *) * lrc_info.len);
                            if(lrc_info.lyrics == NULL) {
                                free(tmp_ptr);
                                goto err2;
                            }
                        }
                    }
                    
                    i += 6;
                }
            }
        } else if(len > 4) {
            for(int i = 0; i < sizeof(idtags)/sizeof(char*); i++) {
                int idtag_len = strlen(idtags[i]);
                if(strncmp(buf, idtags[i], idtag_len)) {
                    continue;
                } else {
                    lrc_info.id_tag[i] = malloc(len - idtag_len + 1);
                    strcpy(lrc_info.id_tag[i], &buf[idtag_len]);
                    lrc_info.id_tag[i][len - idtag_len - 2] = 0;
                    break;
                }
            }
        }
    }
    
    lrc_info.lyric_len = cnt;
    
    qsort(lrc_info.lyrics, lrc_info.lyric_len, sizeof(lrc_lyric_t), compare);
    
    //关闭文件
    fclose(fp);
    
    return 0;
    
err2:
    lrc_free();
    
err1:
    fclose(fp);
    
err0:
    return -1;
}

static int lower_bound(lrc_lyric_t* buf, int len, int key) {
    int l = 0, r = len - 1, ret = len;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (buf[mid].time > key) {
            r = mid - 1;
        } else {
            ret = mid;
            l = mid + 1;
        }
    }
    return ret;
}

/**
  * @brief      获取时间所对应的歌词
  * @param[in]  time : 时间，毫秒为单位
  * @param[in]  returnsize : 歌词行数
  *
  * @return     歌词列表
  */
char** lrc_get_msec_to_lyric(int time, int* returnsize)
{
    *returnsize = 0;
    if(lrc_info.len) {
        int id = lower_bound(lrc_info.lyrics, lrc_info.lyric_len, time);
        if(id < lrc_info.lyric_len) {
            *returnsize = lrc_info.lyrics[id].cnt;
            return lrc_info.lyrics[id].lyric;
        } else {
            return NULL;
        }
    }
    return NULL;
}

/**
  * @brief      获取时间所对应的歌词
  * @param[in]  time : 时间，秒为单位
  * @param[in]  returnsize : 歌词行数
  *
  * @return     歌词列表
  */
char** lrc_get_sec_to_lyric(int time, int* returnsize)
{
    return lrc_get_msec_to_lyric(time * 1000, returnsize);
}

/**
  * @brief      获取时间所对应的行号
  * @param[in]  time : 时间，毫秒为单位
  *
  * @return     行号
  */
int lrc_get_msec_to_line(int time)
{
    if(lrc_info.len) {
        int id = lower_bound(lrc_info.lyrics, lrc_info.lyric_len, time);
        if(id < lrc_info.lyric_len) {
            return id;
        } else {
            return -1;
        }
    }
    return -1;
}

/**
  * @brief      获取时间所对应的行号
  * @param[in]  time : 时间，秒为单位
  *
  * @return     行号
  */
int lrc_get_sec_to_line(int time)
{
    return lrc_get_msec_to_line(time * 1000);
}

/**
  * @brief      获取歌词总行数
  *
  * @return     歌词总行数
  */
int lrc_get_lyric_line(void)
{
    return lrc_info.lyric_len;
}

/**
  * @brief      获取行号所对应的歌词
  * @param[in]  line : 行号
  * @param[in]  returnsize : 歌词行数
  *
  * @return     歌词列表
  */
char** lrc_get_lyric_line_to_lyric(int line, int* returnsize)
{
    *returnsize = 0;
    if(lrc_info.len) {
        if(line >= lrc_info.lyric_len || line < 0) {
            return NULL;
        } else {
            *returnsize = lrc_info.lyrics[line].cnt;
            return lrc_info.lyrics[line].lyric;
        }
    }
    return NULL;
}

/**
  * @brief      获取行号所对应的时间
  * @param[in]  line : 行号
  *
  * @return     时间，毫秒为单位
  */
int lrc_get_lyric_line_to_msec(int line)
{
    if(lrc_info.len) {
        if(line >= 0 && line < lrc_info.lyric_len) {
            return lrc_info.lyrics[line].time;
        }
    }
    
    return -1;
}

/**
  * @brief      获取行号所对应的时间
  * @param[in]  line : 行号
  *
  * @return     时间，秒为单位
  */
int lrc_get_lyric_line_to_sec(int line)
{
    return lrc_get_lyric_line_to_msec(line) >= 0 ? lrc_get_lyric_line_to_msec(line) / 1000 : -1;
}

/**
  * @brief      获取id标签
  *
  * @return     id标签列表
  */
char** lrc_get_id_tag(void)
{
    return lrc_info.id_tag;
}

/**
  * @brief      LRC解析初始化
  *
  * @return     无
  */
void lrc_init(void)
{
    memset(&lrc_info, 0, sizeof(lrc_t));
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{    
    lrc_init();
    
    lrc_parse("青花瓷.lrc");
    
    printf("获取时间所对应的歌词\n");
    for(int i = 0; i < 300; i++) {
        int len = 0;
        char **ret = lrc_get_sec_to_lyric(i, &len);
        
        for(int j = 0; j < len; j++) {
            printf("%03d [%02d:%02d] %s\n", i, i / 60, i % 60, ret[j]);
        }
    }
    printf("\n");
    
    printf("获取行号所对应的歌词\n");
    for(int i = 0; i < lrc_get_lyric_line(); i++) {
        int len = 0;
        char **ret = lrc_get_lyric_line_to_lyric(i, &len);
        
        for(int j = 0; j < len; j++) {
            printf("%03d %s\n", i, ret[j]);
        }
    }
    printf("\n");
    
    printf("获取行号所对应的时间\n");
    for(int i = 0; i < lrc_get_lyric_line(); i++) {
        int t = lrc_get_lyric_line_to_msec(i);
        printf("line %d time %d [%02d:%02d:%03d]\n", i, t, t / 1000 / 60, t / 1000 % 60, t % 1000);
    }
    printf("\n");
    
    printf("获取时间所对应的歌词\n");
    for(int i = 0; i < 90000; i += 100) {//for(int i = 60000; i < 90000; i += 100) {
        int len = 0;
        char **ret = lrc_get_msec_to_lyric(i, &len);
        
        for(int j = 0; j < len; j++) {
            printf("%03d [%02d:%02d:%03d] %s\n", i, i / 1000 / 60, i / 1000 % 60, i % 1000, ret[j]);
        }
    }
    printf("\n");
    
    printf("获取id标签\n");
    char** id_tag = lrc_get_id_tag();
    for(int i = 0; i < LRC_TAG_ID_MAX; i++) {
        if(id_tag[i])
            printf("%s %s\n", &idtags[i][1], id_tag[i]);
    }
    printf("\n");
    
    lrc_free();
    
    return 0;
}
