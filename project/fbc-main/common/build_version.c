#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <version.h>

#define FBC_VERSION_MAIN    1
#define FBC_VERSION_SUB1    1
#define FBC_VERSION_SUB2    0

static char versioninfo[256] = "N/A";
static long long version_serial = 0;
static char gitversionstr[256] = "N/A";

static int fbc_version_info_init(void) {
    static int info_is_inited = 0;
    char git_shor_version[20];
    unsigned int shortgitversion;
    int dirty_num = 0;

    if (info_is_inited > 0) {
        return 0;
    }
    info_is_inited++;

#ifdef FBC_GIT_UNCOMMIT_FILE_NUM
    dirty_num = strtoul(FBC_GIT_UNCOMMIT_FILE_NUM, NULL, 10);
#endif

#ifdef FBC_GIT_COMMIT
    if (dirty_num > 0) {
        sprintf(gitversionstr, "%s-with-%d-dirty-files", FBC_GIT_COMMIT, dirty_num);
    } else {
        sprintf(gitversionstr, "%s", FBC_GIT_COMMIT);
    }
#endif

    memcpy(git_shor_version, gitversionstr, 8);
    git_shor_version[8] = '\0';
    shortgitversion = strtoul(git_shor_version, NULL, 16);
    version_serial = (long long) (FBC_VERSION_MAIN & 0xff) << 56 | (long long) (FBC_VERSION_SUB1 & 0xff) << 48 | (long long) (FBC_VERSION_SUB2 & 0xff) << 32
            | shortgitversion;

    sprintf(versioninfo, "%d.%d.%d.%s", FBC_VERSION_MAIN, FBC_VERSION_SUB1, FBC_VERSION_SUB2, git_shor_version);

    return 0;
}

const char *fbc_get_version_info(void) {
    fbc_version_info_init();
    return versioninfo;
}

const char *fbc_get_git_version_info(void) {
    fbc_version_info_init();
    return gitversionstr;
}

const char *fbc_get_last_chaned_time_info(void) {
#ifdef FBC_GIT_LAST_CHANGED
    return FBC_GIT_LAST_CHANGED;
#else
    return " Unknow ";
#endif
}

const char *fbc_get_git_branch_info(void) {
#ifdef FBC_GIT_BRANCH
    return FBC_GIT_BRANCH;
#else
    return " Unknow ";
#endif
}

const char *fbc_get_build_time_info(void) {
#ifdef FBC_BUILD_TIME
    return FBC_BUILD_TIME;
#else
    return " Unknow ";
#endif
}

const char *fbc_get_build_name_info(void) {
#ifdef FBC_BUILD_NAME
    return FBC_BUILD_NAME;
#else
    return " Unknow ";
#endif
}

void print_build_version_info(void) {
    fbc_version_info_init();

    printf("fbc version:%s\n", fbc_get_version_info());
    printf("fbc git version:%s\n", fbc_get_git_version_info());
    printf("fbc git branch:%s\n", fbc_get_git_branch_info());
    printf("fbc Last Changed:%s\n", fbc_get_last_chaned_time_info());
    printf("fbc Last Build:%s\n", fbc_get_build_time_info());
    printf("fbc Builer Name:%s\n", fbc_get_build_name_info());
    printf("\n");
}
