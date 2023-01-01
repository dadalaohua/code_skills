#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
https://mp.weixin.qq.com/s?__biz=MzU5MzcyMjI4MA==&mid=2247511241&idx=1&sn=d9b982360b4de3ce53c72958c07ba987&chksm=fe0ec20ec9794b18a91a496842876e0275c2c0d993e2f40e0d3a5b103dc0c3b9ecc39c146f0c&scene=21#wechat_redirect
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SHELL_CMD_MODIFY_WIFI_SSID        "sed -i \'s/ssid=\"[^\"]*\"/ssid=\"%s\"/g\' ./wpa_supplicant.conf"
#define SHELL_CMD_MODIFY_WIFI_PSW         "sed -i \'s/psk=\"[^\"]*\"/psk=\"%s\"/g\' ./wpa_supplicant.conf"
#define SHELL_CMD_RESET_WIFI_CONF_FILE    "cp default_wpa_supplicant.conf wpa_supplicant.conf"


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char shell_cmd[256] = {0};

    // 重置WiFi配置文件
    system(SHELL_CMD_RESET_WIFI_CONF_FILE);

    // 修改WiFi名称
    snprintf(shell_cmd, sizeof(shell_cmd), SHELL_CMD_MODIFY_WIFI_SSID, "Hello");
    system(shell_cmd);

    // 清除shell_cmd
    bzero(shell_cmd, sizeof(shell_cmd));

    // 修改WiFi密码
    snprintf(shell_cmd, sizeof(shell_cmd), SHELL_CMD_MODIFY_WIFI_PSW, "88888888");
    system(shell_cmd);

    return 0;
}