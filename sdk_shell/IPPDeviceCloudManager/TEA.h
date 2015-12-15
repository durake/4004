/*
 * TEA_beta_1.0.h
 *
 *  Created on: 2015年5月5日
 *      Author: liuwen
 */

#ifndef INC_IPPDEVICECLOUDMANAGER_TEA_BETA_10_H_
#define INC_IPPDEVICECLOUDMANAGER_TEA_BETA_10_H_

char* tea_encry(const char* content, const char* key, unsigned int rounds);

char* tea_decry(char* encrypt, const char* key, unsigned int rounds);

#endif /* INC_IPPDEVICECLOUDMANAGER_TEA_BETA_10_H_ */
