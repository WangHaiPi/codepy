/*
* codepy.h - Execute Python code in C++
* 
* Copyright (c) 2026 WangHaipi
* 
* 中文简介：
* 这是一个头文件库，让你能在 C++ 中直接写 Python 代码。
* 就像这样：
*   py << "print('hello')";
*   py.run();
* 
* English Description:
* A header-only library to write Python code in C++.
* Usage:
*   py << "print('hello')";
*   py.run();
* 
* License: MIT
* https://github.com/WangHaipi/codepy
*/
#ifndef CODEPY_H
#define CODEPY_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <codecvt>
#include <locale>
#ifdef _WIN32
	#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
	#include <iconv.h>
#endif
namespace codepy {
	const std::string MIRROR_TUNA = "https://pypi.tuna.tsinghua.edu.cn/simple";
	const std::string MIRROR_ALIYUN = "https://mirrors.aliyun.com/pypi/simple";
	const std::string MIRROR_DOUBAN = "https://pypi.doubanio.com/simple";
	const std::string MIRROR_USTC = "https://mirrors.ustc.edu.cn/pypi/simple";
	const std::string MIRROR_TENCENT = "https://mirrors.cloud.tencent.com/pypi/simple";
	const std::string MIRROR_HUAWEI = "https://mirrors.huaweicloud.com/repository/pypi/simple";
	const std::string MIRROR_NJU = "https://mirror.nju.edu.cn/pypi/web/simple";
	const std::string MIRROR_SJTU = "https://mirror.sjtu.edu.cn/pypi/web/simple";
	const std::string MIRROR_PKU = "https://mirrors.pku.edu.cn/pypi/web/simple";
	const std::string MIRROR_BFSU = "https://mirrors.bfsu.edu.cn/pypi/web/simple";
	class Python {
	private:
		std::string code_buffer;
		std::string current_mirror;
		std::mt19937 rng;
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
#elif defined(__linux__) || defined(__APPLE__)
			iconv_t cd = iconv_open("UTF-8", "GBK");
			if (cd == (iconv_t)-1) return str;
			char* inbuf = const_cast<char*>(str.c_str());
			size_t inbytes = str.size();
			size_t outbytes = inbytes * 4;
			char* outbuf = new char[outbytes];
			char* outptr = outbuf;
			iconv(cd, &inbuf, &inbytes, &outptr, &outbytes);
			iconv_close(cd);
			std::string result(outbuf, outptr - outbuf);
			delete[] outbuf;
			return result;
#else
			return str;
#endif
		}
		
	public:
		Python() : rng(std::random_device{}()) {
			current_mirror=MIRROR_TUNA;
		}
		Python& operator<<(const std::string& py_code) {
			code_buffer += py_code + "\n";
			return *this;
		}
		void run() {
			if (code_buffer.empty()) return;
			std::uniform_int_distribution<int> dist(0, 999999);
			std::string filename = "temp_codepy_" + std::to_string(dist(rng)) + ".py";
			std::ofstream file(filename);
			file << "# -*- coding: utf-8 -*-\n";
			file << "import sys\n";
			file << "import io\n";
			file << "sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')\n";
			std::string utf8_code = to_utf8(code_buffer);
			file << utf8_code;
			file.close();
			std::string cmd = "python " + filename;
			system(cmd.c_str());
			std::remove(filename.c_str());
			code_buffer.clear();
		}
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
		void piplist(){system("pip list");}
		bool has_python() {
#ifdef _WIN32
			return system("python --version 2>nul") == 0;
#else
			return system("python3 --version 2>/dev/null") == 0 ||
			system("python --version 2>/dev/null") == 0;
#endif
		}
		bool has_package(const std::string& pkg) {
			std::string cmd = "python -c \"import " + pkg + "\" 2>null";
			return system(cmd.c_str()) == 0;
		}
		
	};
	
} // namespace codepy

static codepy::Python py;

#endif

