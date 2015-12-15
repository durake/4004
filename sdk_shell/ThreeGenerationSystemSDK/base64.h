/*
 * base64.h
 *
 *  Created on: Oct 28, 2015
 *      Author: ghy
 */

#ifndef BASE64_H_
#define BASE64_H_

char* base64_encode(const char* data, int data_len);
char *base64_decode(const char* data, int data_len);

#endif /* BASE64_H_ */
