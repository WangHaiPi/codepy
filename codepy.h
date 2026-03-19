// codepy.h
#ifndef CODEPY_H
#define CODEPY_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <codecvt>
#include <locale>
#include <windows.h>
namespace codepy {
	const std::string MIRROR_TUNA = "https://pypi.tuna.tsinghua.edu.cn/simple";
	const std::string MIRROR_ALIYUN = "https://mirrors.aliyun.com/pypi/simple";
	const std::string MIRROR_DOUBAN = "https://pypi.doubanio.com/simple";
	const std::string MIRROR_USTC = "https://mirrors.ustc.edu.cn/pypi/simple";
	const std::string MIRROR_TENCENT = "https://mirrors.cloud.tencent.com/pypi/simple";
	const std::string MIRROR_HUAWEI = "https://mirrors.huaweicloud.com/repository/pypi/simple";
	const std::string MIRROR_NJU = "https://mirror.nju.edu.cn/pypi/web/simple";      // 南大
	const std::string MIRROR_SJTU = "https://mirror.sjtu.edu.cn/pypi/web/simple";     // 交大
	const std::string MIRROR_PKU = "https://mirrors.pku.edu.cn/pypi/web/simple";      // 北大
	const std::string MIRROR_BFSU = "https://mirrors.bfsu.edu.cn/pypi/web/simple";    // 北外
	class Python {
	private:
		std::string code_buffer;
		std::string current_mirror;
		// Windows 下转换编码
		std::string to_utf8(const std::string& str) {
#ifdef _WIN32
			int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
			wchar_t* wstr = new wchar_t[len];
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
			
			len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
			char* ustr = new char[len];
			WideCharToMultiByte(CP_UTF8, 0, wstr, -1, ustr, len, NULL, NULL);
			
			std::string result(ustr);
			delete[] wstr;
			delete[] ustr;
			return result;
#else
			return str;
#endif
		}
		
	public:
		Python() {
			std::srand(static_cast<unsigned>(std::time(nullptr)));
			current_mirror = MIRROR_TUNA;
		}
		
		// 添加 Python 代码
		Python& operator<<(const std::string& py_code) {
			code_buffer += py_code + "\n";
			return *this;
		}
		
		// 执行代码
		void run() {
			if (code_buffer.empty()) return;
			
			// 生成临时 Python 文件
			std::string filename = "temp_codepy_" + std::to_string(rand()) + ".py";
			std::ofstream file(filename);
			
			// 写入编码声明
			file << "# -*- coding: utf-8 -*-\n";
			file << "import sys\n";
			file << "import io\n";
			file << "sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')\n";
			
			// 写入代码（转换编码）
			std::string utf8_code = to_utf8(code_buffer);
			file << utf8_code;
			file.close();
			
			// 调用系统 Python 执行
			std::string cmd = "python " + filename;
			system(cmd.c_str());
			
			// 删除临时文件
			std::remove(filename.c_str());
			
			// 清空缓冲区
			code_buffer.clear();
		}
		
		// 直接执行单行
		void exec(const std::string& line) {
			*this << line;
			run();
		}
		void pip(const std::string& pack) {
			std::string cmd = "pip install " + pack;
			system(cmd.c_str());
		}
		void pipun(const std::string& pack) {
			std::string cmd = "pip uninstall " + pack;
			system(cmd.c_str());
		}
		void set_mirror(const std::string& mirror) {
			current_mirror = mirror;
		}
	};
	
} // namespace codepy

static codepy::Python py;

#endif
