#pragma once
#include <iostream>
#include <io.h>
#include <string>
#include <list>
using namespace std;

string Contents;

void searchingDir(string path, int depth);
int isFileOrDir(_finddata_t fd);
void stringProcess(string s, string path, const int& checkDirFile);

int main() {
	string path = "D:\\0JWK\\0programming\\PS-Reference-Codes\\Reference Codes";
	searchingDir(path, 0);
	cout << Contents << '\n';
}

void searchingDir(string path, int depth) {
	if (depth >= 2) return;

	int checkDirFile = 0;
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;
	intptr_t handle;
	list<_finddata_t> fdlist;

	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) {
		cout << "No file in directory!" << endl;
		return;
	}

	do {
		checkDirFile = isFileOrDir(fd);
		if (fd.name[0] != '.') {
			stringProcess(fd.name, path, checkDirFile);

			if (checkDirFile == 0) searchingDir(path + "\\" + fd.name, depth + 1);
			else fdlist.push_back(fd);
		}

	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);
}

int isFileOrDir(_finddata_t fd) {
	if (fd.attrib & _A_SUBDIR) return 0;
	else return 1;
}

void stringProcess(string s, string path, const int& checkDirFile) {
	//목차 이름 구하기
	bool first = true;
	for (int i = 0; i < s.size(); i++) {
		Contents.push_back(s[i]);
		if (first && s[i] == ' ') {
			Contents.push_back('[');
			first = false;
		}
	}
	if (checkDirFile == 1) { //.txt 떼기
		for (int i = 0; i < 4; i++) Contents.pop_back();
	}
	Contents.push_back(']');

	//하이퍼링크 주소 구하기
	Contents.push_back('(');
	if (checkDirFile == 0) {
		Contents += "https://github.com/manoflearning/PS-Reference-Codes/tree/master/";
	}
	else {
		Contents += "https://github.com/manoflearning/PS-Reference-Codes/blob/master/";
	}
	for (int i = 38; i < path.size(); i++) {
		if (path[i] == ' ') Contents += "%20";
		else {
			if (path[i] == '\\') Contents.push_back('/');
			else Contents.push_back(path[i]);
		}
	}
	Contents.push_back('/');
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ' ') Contents += "%20";
		else Contents.push_back(s[i]);
	}
	Contents.push_back(')');
	
	Contents += " <br/>\n";
}

/* 인터넷에서 찾은 코드
#pragma once

#include <iostream> //I/O스트림 헤더
#include <io.h> //파일 구조체 헤더
#include <string>//스트링 객체 사용 헤더
#include <list>//리스트 자료형 헤더
using namespace std;

void searchingDir(string path);
int isFileOrDir(_finddata_t fd);

int main() {

	string path = "C:\\DEV\\test";
	searchingDir(path);

}

void searchingDir(string path)
{
	int checkDirFile = 0;
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;//디렉토리 내 파일 및 폴더 정보 저장 객체
	intptr_t handle;
	list<_finddata_t> fdlist;//디렉토리, 파일 정보 객체 리스트

	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) //fd 구조체 초기화.
	{
		//파일이나 디렉토리가 없을 경우.
		cout << "No file in directory!" << endl;
		return;
	}

	do //폴더 탐색 반복 시작
	{
		checkDirFile = isFileOrDir(fd);//현재 객체 종류 확인(파일 or 디렉토리)
		if (checkDirFile == 0 && fd.name[0] != '.') {
			//디렉토리일 때의 로직
			cout << "Dir  : " << path << "\\" << fd.name << endl;
			searchingDir(path + "\\" + fd.name);//재귀적 호출
		}
		else if (checkDirFile == 1 && fd.name[0] != '.') {
			//파일일 때의 로직
			cout << "File : " <<path<<"\\"<< fd.name << endl;
			fdlist.push_back(fd);
		}

	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);
}

int isFileOrDir(_finddata_t fd)
//파일인지 디렉토리인지 판별
{

	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}*/