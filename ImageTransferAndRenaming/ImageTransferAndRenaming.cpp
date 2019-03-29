#include "pch.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

//Transfering all images from 172.19.144.55 server to local machine
void foo(string folder, string file)
{
	stringstream ss;
	ss << "robocopy \\\\172.19.144.55\\cablelabs1.1-1\\" + folder + " images " + folder + "_" + file + ".jpg";

	string commandLine = ss.str();

	//examine the commandline!
	cout << commandLine << "\n";

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	char *buf = _strdup(commandLine.c_str());
	CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(buf);
	WaitForSingleObject(pi.hProcess, INFINITE);
}

//Transfering all renamed images from local machine to 172.19.144.18 server
void foo2(string file)
{
	stringstream ss;
	ss << "robocopy images \\\\172.19.144.18\\moviedata\\thumbnails " + file + ".jpg";

	string commandLine = ss.str();

	//examine the commandline!
	cout << commandLine << "\n";

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	char *buf = _strdup(commandLine.c_str());
	CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(buf);
	WaitForSingleObject(pi.hProcess, INFINITE);
}

//Transfering all renamed images from local machine to 172.19.144.74 server
void foo3(string file)
{
	stringstream ss;
	ss << "robocopy images \\\172.19.144.74\\moviedata\\thumbnails " + file + ".jpg";

	string commandLine = ss.str();

	//examine the commandline!
	cout << commandLine << "\n";

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	char *buf = _strdup(commandLine.c_str());
	CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(buf);
	WaitForSingleObject(pi.hProcess, INFINITE);
}

//Transfering all renamed images from local machine to 172.19.144.93 server
void foo4(string file)
{
	stringstream ss;
	ss << "robocopy images \\\\172.19.144.93\\thumbnails " + file + ".jpg";

	string commandLine = ss.str();

	//examine the commandline!
	cout << commandLine << "\n";

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	char *buf = _strdup(commandLine.c_str());
	CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(buf);
	WaitForSingleObject(pi.hProcess, INFINITE);
}

//Transfering all renamed images from local machine to 172.19.144.94 server
void foo5(string file)
{
	stringstream ss;
	ss << "robocopy images \\\\172.19.144.94\\thumbnails " + file + ".jpg";

	string commandLine = ss.str();

	//examine the commandline!
	cout << commandLine << "\n";

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	memset(&pi, 0, sizeof(pi));

	char *buf = _strdup(commandLine.c_str());
	CreateProcessA(0, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	free(buf);
	WaitForSingleObject(pi.hProcess, INFINITE);
}

int main()
{
	string test;
	string s;
	cout << "Start" << endl;

	struct file {
		string oldName;
		string newName;
		string height;
		string width;
	};

	vector<file> list;

	ifstream infile2;
	infile2.open("images.txt");

	if (infile2.fail())
	{
		cout << "Could not open images.txt file." << "\n";
		return 1;
	}
	string data;//reading data from list of images with full name
	//Reading data from file with all images names with image w and h and asset IDs
	while (infile2 >> data) {
		file tempf;
		tempf.oldName = data;
		infile2 >> data;
		tempf.newName = data;
		infile2 >> data;
		tempf.height = data;
		infile2 >> data;
		tempf.width = data;
		list.push_back(tempf);
	}

	vector<string> assetIds;
	assetIds.push_back(list[0].oldName);

	for (int i = 1; i < list.size(); i++) {
		if (assetIds[assetIds.size() - 1] != list[i].oldName)
			assetIds.push_back(list[i].oldName);
	}

	//Procedures for every image copying from server to local
	string imagesExtensions[8] = { "box_cover", "image1" , "image2" , "image3" , "image4", "image5" , "image6" , "poster" };
	for (int i = 0; i < assetIds.size(); i++)
		for (int j = 0; j < 8; j++)
			foo(assetIds[i], imagesExtensions[j]);

	string listOfHeights[8] = { "480" , "120" , "160" , "170" , "300" , "375" , "375" , "1280" };
	string listOfWidths[8] = { "720" , "150" , "149" , "160" , "300" , "200" , "384" , "720" };

	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < 8; j++) {
			string oldName = "images\\" + list[i].oldName + "_" + imagesExtensions[j] + ".jpg";
			cout << "OldName: " << oldName << " New Name:" << list[i].newName << endl;
			rename(oldName.c_str(), ("images\\" + list[i].newName + ".jpg").c_str());
		}

	}

	for (int i = 0; i < list.size(); i++) {
		foo2(list[i].newName);
	}

	for (int i = 0; i < list.size(); i++) {
		foo3(list[i].newName);
	}

	for (int i = 0; i < list.size(); i++) {
		foo4(list[i].newName);
	}

	for (int i = 0; i < list.size(); i++) {
		foo5(list[i].newName);
	}

	return 0;
}