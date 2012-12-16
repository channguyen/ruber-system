/***************************************************************************
 * Class:		Comp 465 Fall 2012 - Computer Graphics Systems and Design  *
 * Instructor:	Dr. Mike Barnes										       *
 * Project:		Target Practice P3	                                       *
 * Due Date:	12/07/2012												   *
 * Students:    Chan Nguyen  - ngocchan.nguyen.61@my.csun.edu              *
 *				Lianhua Shen - lianhua.shen.124@my.csun.edu                *
 ***************************************************************************/
#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <sstream>

using namespace std;

namespace util {
	template <typename T>
	string to_string(const T &data) {
		ostringstream ostr;
		ostr << data;
		return ostr.str();
	}
}

#endif