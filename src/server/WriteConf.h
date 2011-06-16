/*
 * WriteConf.h
 *
 *  Created on: 19/04/2011
 *      Author: Jose Luis Lafuente
 */

#ifndef WRITECONF_H_
#define WRITECONF_H_
#include <fstream>

using namespace std;


class WriteConf {
public:
	WriteConf();
	virtual ~WriteConf();
	void writeLog();
	void setText(string);

private:
	ofstream file;
	string text;
};

#endif /* WRITECONF_H_ */
