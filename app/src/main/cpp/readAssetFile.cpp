//
// Created by sqwu on 2020/5/13.
//
#include <android/asset_manager_jni.h>
#include "log.h"
#include "iostream"
#include <vector>
#include "jni.h"

static AAssetManager *gAssetMgr;

void printVector(std::vector<char> data){

    std::string s;
    for (int i = 0; i < data.size(); ++i) {
        s += data[i];
    }
    LOGE("TAG", "打印行数据%s", s.data());


}

void loadAssetsData(JNIEnv *env,
                    jobject thiz,
                    jobject asset_manager,
                    jstring jdata_path,
                    jstring jmodel_path){
// TODO: implement start()
    // TODO: implement start()
    gAssetMgr = AAssetManager_fromJava(env, asset_manager);
    const char *fileName = env->GetStringUTFChars(jdata_path, 0);
//    string s(fileName);
    const char *TAG = "测试输出：";
    LOGE(TAG, "%s", fileName);
    AAsset *asset = AAssetManager_open(gAssetMgr, fileName, AASSET_MODE_UNKNOWN);
    if (asset != NULL) {
        off_t bufSize = AAsset_getLength(asset);
        if (bufSize > 0) {

            int readSize = 0;
            long index = 0;
            int readUnit = 1;
            char *buffer = new char[readUnit];
            std::vector<char> lineData;
            int  row = 0;
            do {

                index = readUnit;
                readSize = AAsset_read(asset, buffer, readUnit);
                //剩余数据长度
                off_t remain = AAsset_getRemainingLength(asset);
                AAsset_seek(asset, 0, index);

                if (readSize > 0) {
                    if (*buffer == '\n'){


                        if(row < 3 || row > 6388) {
                            LOGE(TAG, "第%d行,长度为%d", row + 1, lineData.size());
                            printVector(lineData);
                        }
                        std::vector<char> ss;
                        lineData = ss;
                        row++;
                    }else{
                        lineData.push_back(*buffer);
                    }
                }

            } while (readSize > 0);

            LOGE(TAG, "第%d行,长度为%d", row + 1, lineData.size());
            printVector(lineData);

            LOGE(TAG, "%s", "执行完成");
            free(buffer);
            AAsset_close(asset);

        }
    }
}