//
// Created by zhukovasky on 2020/8/4.
//

#ifndef JAVAP_FILEUTILS_H
#define JAVAP_FILEUTILS_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <sstream>
#include "StringUtils.h"

namespace fs=boost::filesystem;
using namespace std;
namespace Utils {
    class FileUtils {
        //查看指定文件夹下所有文件
    public :
        inline static bool listFiles(std::string destDir, std::vector<std::string> &fileVectors) {
            if (!fs::exists(destDir)) {
                //  Log::LogUtils::getLogUtilsInstance()->error("对应文件夹不存在 %s",destDir);
                return false;
            }
            if (!fs::is_directory(destDir)) {
                // Log::LogUtils::getLogUtilsInstance()->error("对应路径非文件夹 %s",destDir);
                return false;
            };
            fs::directory_iterator iter_begin(destDir);
            fs::directory_iterator iter_end;
            for (; iter_begin != iter_end; iter_begin++) {
                fs::path path_tmp(*iter_begin);
                if (fs::is_regular_file(path_tmp)) {
                    path_tmp = path_tmp.filename();
                    std::string str = path_tmp.string();
                    fs::is_regular_file(str);
                    fileVectors.push_back(str);
                }
            }
            return true;
        }


        inline static bool listJarOrZipFile(std::string destDir,std::list<std::string> &fileList,std::string suffix){
            if (!fs::exists(destDir)) {
                //  Log::LogUtils::getLogUtilsInstance()->error("对应文件夹不存在 %s",destDir);
                return false;
            }
            if (!fs::is_directory(destDir)) {
                // Log::LogUtils::getLogUtilsInstance()->error("对应路径非文件夹 %s",destDir);
                return false;
            };
            fs::directory_iterator iter_begin(destDir);
            fs::directory_iterator iter_end;
            for (; iter_begin != iter_end; iter_begin++) {
                fs::path path_tmp(*iter_begin);
                if (fs::is_regular_file(path_tmp)) {
                    path_tmp = path_tmp.filename();
                    std::string str = path_tmp.string();
                    fs::is_regular_file(str);
                    if(Utils::StringUtils::endsWith(str,suffix)){
                        fileList.push_back(str);
                    }
                }
            }
            return true;
        }

        static std::string readFileContent(std::string filePath) {


            std::ifstream filestream(filePath, ios::in | ios::binary);
            std::stringstream buffer;
            buffer << filestream.rdbuf();
            std::string contents(buffer.str());
            filestream.close();
            return contents;
        }


    };
}


#endif //JAVAP_FILEUTILS_H
