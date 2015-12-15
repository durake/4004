#ifndef _TEA_BETA_1_0_H_
#define _TEA_BETA_1_0_H_

char* tea_encry(const char* content, const char* key, unsigned int rounds);
char* tea_decry(char* encrypt, const char* key, unsigned int rounds);

#endif
