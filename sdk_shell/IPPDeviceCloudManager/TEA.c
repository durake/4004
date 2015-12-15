/******************************/
/***2014骞�12鏈�23鏃�**************/

#ifdef LINUX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#include "ipp_stub_def.h"


/**
 * 鍩烘湰鐨�8bytes鏁版嵁鍧楀姞瀵�
 * param unsigned long v[2] 8bytes data
 * param const unsigned long k[4 16bytes key
 * return unsigned long v[2] 8bytes data
 * unsigned long rounds 鍔犲瘑杞暟鍙��16鎴�32
 */
void inner_encrypt(unsigned int v[2],const unsigned int k[4],unsigned int rounds){
 register unsigned int
  y=v[0],z=v[1],sum=0,delta=0x9E3779B9,
  a=k[0],b=k[1],c=k[2],d=k[3];
 while(rounds-->0){
  sum+=delta;
  y+=((z<<4)+a)^(z+sum)^((z>>5)+b);
  z+=((y<<4)+c)^(y+sum)^((y>>5)+d);
 }
 v[0]=y;
 v[1]=z;
}




/**
 * 鍩烘湰鐨�8bytes鏁版嵁鍧楄В瀵�
 * param unsigned long v[2] 8bytes data
 * param const unsigned long k[4 16bytes key
 * return unsigned long v[2] 8bytes data
 * unsigned long rounds 鍔犲瘑杞暟鍙��16鎴�32
 */
void inner_decrypt(unsigned int v[2],const unsigned int k[4],unsigned int rounds){
 register unsigned int
  y=v[0],z=v[1],delta=0x9E3779B9,
  a=k[0],b=k[1],c=k[2],d=k[3],sum;
if(rounds==32)
        sum=0xc6ef3720;
    else if(rounds==16)
        sum=0xe3779b90;
    else return;
 while(rounds-->0){
  z-=((y<<4)+c)^(y+sum)^((y>>5)+d);
  y-=((z<<4)+a)^(z+sum)^((z>>5)+b);
  sum-=delta;
 }
 v[0]=y;
 v[1]=z;
}



/**add the flag to encrypted content
 * char* unflag: the encrypted content without flag
 * int len:the len of the encrypted content
 */

char *flag(char *unflag,int len)
{
char flag[9]="}}}}}}}}";
char *flag_out=(char*)malloc(len+8);
memcpy(flag_out,flag,8);
memcpy(flag_out+8,unflag,len);
free(unflag);
return flag_out;

}



/**remove the flagwords from the content
 * char* flag content contains flag
 * int len: length of the content
 */
char *unflag(const char *flag,int len)
{
char *unflag=(char*)malloc(len-8);
memcpy(unflag,flag+8,len-9);
free((void*)flag);
return unflag;
}


/**transform byte to hexString
 * encrypted content
 * length of the content the value is the length of the encrypted
 */
char* byte2hex(char* encrypt,int len){
 int i=0;
 int j;

 char* out=(char*)malloc((2*len+1)*sizeof(char));
 for(j=0;i<len;i++,j+=2)
   {
   char tempchar1='0'+((encrypt[i]&0xf0) >> 4);
   char tempchar2='0'+((encrypt[i]&0x0f));
  if(tempchar1 > '9')
      switch(tempchar1-'9'){
           case 1: tempchar1='A';  break;
           case 2: tempchar1='B';  break;
           case 3: tempchar1='C';  break;
           case 4: tempchar1='D';  break;
           case 5: tempchar1='E';  break;
           case 6: tempchar1='F';  break;
              } 
  if(tempchar2 > '9')
      switch(tempchar2-'9'){
           case 1: tempchar2='A';  break;
           case 2: tempchar2='B';  break;
           case 3: tempchar2='C';  break;
           case 4: tempchar2='D';  break;
           case 5: tempchar2='E';  break;
           case 6: tempchar2='F';  break;
              } 

out[j]=tempchar1;
out[j+1]=tempchar2;
}
out[2*len]='\0';
 free(encrypt);               
return out;
}



/**recover hex to byte(char*)
 *hex: hexString
 *out:to stores the result
 */ 
 void hex2byte(char* hex, char out[]){
 int i=0;
 int j=0;
 int temps=0;
 int temps1=0;

for(;i<strlen(hex)/2;i++,j+=2){


if(hex[j]<'0'||hex[j]>'9'){
switch (hex[j]){
case 'A': temps=10;break;
case 'B': temps=11;break; 
case 'C': temps=12;break;
case 'D': temps=13;break;
case 'E': temps=14;break;
case 'F': temps=15;break;
 }
}
else temps=hex[j]-'0';



if(hex[j+1]<'0'||hex[j+1]>'9'){
switch(hex[j+1]){
case 'A': temps1=10;break;
case 'B': temps1=11;break; 
case 'C': temps1=12;break;
case 'D': temps1=13;break;
case 'E': temps1=14;break;
case 'F': temps1=15;break;
}
}
else temps1=hex[j+1]-'0';
out[i]=(char)((temps&0x0000000f)<<4)|(temps1&0x0000000f);
}

}



/**瀵嗛挜璁惧畾鍑芥暟 閫夊彇16浣峛yte鍨嬩綔涓哄墠8byte鍔犲瘑瀵嗛挜 浠庡師濮嬪瓧绗︿覆涓n浣嶅紑濮嬪彇8byte  鑻ヤ笉婊�8byte 琛ラ浂  涔嬪悗8byte琛ヤ綅 涓�127-n-i
  * @param key 鍘熷杈撳叆鐨勫瘑閽ュ瓧绗︿覆
  * @return 杩斿洖鍔犺В瀵嗗瘑閽�
  */
void validateKey(const char* key,unsigned int k[4]){
int n=6;
char tempkey[17];
if (strlen(key)-n+1<8){
int i,j;
for(i=n-1,j=0;i<strlen(key);i++,j++)
{
   tempkey[j] = key [i];
}
for(;j<8;j++)
 tempkey[j]=0;
for(;j<16;j++)
  tempkey[j]=127-n-j;

    k[0]=((tempkey[0]&0x000000FF)<<24)|
   ((tempkey[1]&0x000000FF)<<16)|
   ((tempkey[2]&0x000000FF)<<8)|
   ( tempkey[3]&0x000000FF);
 k[1]=((tempkey[4]&0x000000FF)<<24)|
   ((tempkey[5]&0x000000FF)<<16)|
   ((tempkey[6]&0x000000FF)<<8)|
   ( tempkey[7]&0x000000FF);
 k[2]=((tempkey[8]&0x000000FF)<<24)|
   ((tempkey[9]&0x000000FF)<<16)|
   ((tempkey[10]&0x000000FF)<<8)|
   ( tempkey[11]&0x000000FF);
 k[3]=((tempkey[12]&0x000000FF)<<24)|
   ((tempkey[13]&0x000000FF)<<16)|
   ((tempkey[14]&0x000000FF)<<8)|
   ( tempkey[15]&0x000000FF);
    
}
else {
int i,j;
   for(i=n-1,j=0;i<n+8;i++,j++)
    tempkey[j]= key[i];
   for(j=8;j<16;j++)
    tempkey[j]= 127-n-j;
     k[0]=((tempkey[0]&0x000000FF)<<24)|
   ((tempkey[1]&0x000000FF)<<16)|
   ((tempkey[2]&0x000000FF)<<8)|
   ( tempkey[3]&0x000000FF);
 k[1]=((tempkey[4]&0x000000FF)<<24)|
   ((tempkey[5]&0x000000FF)<<16)|
   ((tempkey[6]&0x000000FF)<<8)|
   ( tempkey[7]&0x000000FF);
 k[2]=((tempkey[8]&0x000000FF)<<24)|
   ((tempkey[9]&0x000000FF)<<16)|
   ((tempkey[10]&0x000000FF)<<8)|
   ( tempkey[11]&0x000000FF);
 k[3]=((tempkey[12]&0x000000FF)<<24)|
   ((tempkey[13]&0x000000FF)<<16)|
   ((tempkey[14]&0x000000FF)<<8)|
   ( tempkey[15]&0x000000FF);

}
}

/**
 * 鏍￠獙瀵嗛挜,濡傛灉涓嶈冻16瀛楄妭鍒欐湯灏惧～鍏呭瓧鑺�0琛ヨ冻16瀛楄妭,濡傛灉澶т簬16瀛楄妭鍒欎涪寮冩湯灏惧浣欑殑瀛楄妭
 * param const char*
 * return int k[4] 闀垮害涓�4鐨勫洓瀛楄妭绫诲瀷鏁扮粍
 */
/*void validateKey(const char* key,unsigned long k[4]){
 char tmp[16];
 int i=0;
 int klen=strlen(key);
 if(klen<16){
  for(;i<klen;i++){
   tmp[i]=key[i];
  }
  for(;i<16;i++){ 
   tmp[i]='\0';
  }
 }
 else{
  for(;i<16;i++){ 
   tmp[i]=key[i];
  }
 }
 k[0]=((tmp[0]&0x000000FF)<<24)|
   ((tmp[1]&0x000000FF)<<16)|
   ((tmp[2]&0x000000FF)<<8)|
   ( tmp[3]&0x000000FF);
 k[1]=((tmp[4]&0x000000FF)<<24)|
   ((tmp[5]&0x000000FF)<<16)|
   ((tmp[6]&0x000000FF)<<8)|
   ( tmp[7]&0x000000FF);
 k[2]=((tmp[8]&0x000000FF)<<24)|
   ((tmp[9]&0x000000FF)<<16)|
   ((tmp[10]&0x000000FF)<<8)|
   ( tmp[11]&0x000000FF);
 k[3]=((tmp[12]&0x000000FF)<<24)|
   ((tmp[13]&0x000000FF)<<16)|
   ((tmp[14]&0x000000FF)<<8)|
   ( tmp[15]&0x000000FF);
}*/




/**
 * 浠绘剰瀛楄妭鍧楃殑鍔犲瘑
 * param const char* content 浠绘剰闀垮害
 * param const char* key 瀵嗛挜
 * return char* out 鍔犲瘑鍚庡唴瀹瑰瓧鑺傞暱搴﹀繀涓�8鐨勬暣鏁板��
 * unsigned long rounds 鍔犲瘑杞暟鍙��16鎴�32
 */
char* t_encrypt(const char* content,const char* key,unsigned int rounds){

 
 int clen=strlen(content);
 //printf("en_clen=%d\n",clen);
 int csize;
 if(clen%8!=0)
  csize=clen+8-clen%8;
 else
   csize=clen;
//printf("csize:%d\n",csize);
char* out=(char*)malloc(csize+1);

 //int klen=strlen(key);
 int mol=clen%8;
 int size=clen;
 int times=0;
 int i=0,ii=0;
 unsigned int v[2];
 unsigned int k[4];
 //if(clen==0||klen==0){//鑻ュ嚭鐜拌繑鍥炰负绌虹殑鐘跺喌鍙兘閫犳垚鍐呭瓨娉勬紡
 // free(out);
  //return NULL;
// } 
 if(mol!=0){
  size=size+8-mol;
 }
 validateKey(key,k);
 times=size-8;
 //int line=0;
 for(;i<times;i+=8){
  //ii=i;
  v[0]=((content[i]&0x000000FF)<<24)|((content[i+1]&0x000000FF)<<16)|((content[i+2]&0x000000FF)<<8)|(content[i+3]&0x000000FF);
  v[1]=((content[i+4]&0x000000FF)<<24)|((content[i+5]&0x000000FF)<<16)|((content[i+6]&0x000000FF)<<8)|(content[i+7]&0x000000FF);
  inner_encrypt(v,k,rounds);
  //ii=i;
  out[i]  =(char)(v[0]>>24);
  out[i+1]=(char)(v[0]>>16);
  out[i+2]=(char)(v[0]>>8);
  out[i+3]=(char)(v[0]);
  out[i+4]=(char)(v[1]>>24);
  out[i+5]=(char)(v[1]>>16);
  out[i+6]=(char)(v[1]>>8);
  out[i+7]=(char)(v[1]);
 
 }
 ii=i;
 if(mol!=0){
  for(;i<clen;i++){
   out[i]=content[i];
  }
  for(;i<size;i++){
   out[i]='\0';
  }
  i=ii;
  v[0]=((out[i]&0x000000FF)<<24)|((out[i+1]&0x000000FF)<<16)|((out[i+2]&0x000000FF)<<8)|( out[i+3]&0x000000FF);
  v[1]=((out[i+4]&0x000000FF)<<24)|((out[i+5]&0x000000FF)<<16)|((out[i+6]&0x000000FF)<<8)|(out[i+7]&0x000000FF);
  inner_encrypt(v,k,rounds);
  //ii=i;
  out[i]  =(char)(v[0]>>24);
  out[i+1]=(char)(v[0]>>16);
  out[i+2]=(char)(v[0]>>8);
  out[i+3]=(char)(v[0]);
  out[i+4]=(char)(v[1]>>24);
  out[i+5]=(char)(v[1]>>16);
  out[i+6]=(char)(v[1]>>8);
  out[i+7]=(char)(v[1]);

 }
 else{
  v[0]=((content[i]&0x000000FF)<<24)|((content[i+1]&0x000000FF)<<16)|((content[i+2]&0x000000FF)<<8)|(content[i+3]&0x000000FF);
  v[1]=((content[i+4]&0x000000FF)<<24)|((content[i+5]&0x000000FF)<<16)|((content[i+6]&0x000000FF)<<8)|(content[i+7]&0x000000FF);
  inner_encrypt(v,k,rounds);
  //ii=i;
  out[i]  =(char)(v[0]>>24);
  out[i+1]=(char)(v[0]>>16);
  out[i+2]=(char)(v[0]>>8);
  out[i+3]=(char)(v[0]);
  out[i+4]=(char)(v[1]>>24);
  out[i+5]=(char)(v[1]>>16);
  out[i+6]=(char)(v[1]>>8);
  out[i+7]=(char)(v[1]);
 }
out[csize]='\0';
return flag(out,csize+1);

}




/**
 * 浠绘剰瀛楄妭鍧楃殑瑙ｅ瘑
 * param const char* content 浠绘剰闀垮害
 * param const char* key 瀵嗛挜
 * return char* out 瑙ｅ瘑鍚庡唴瀹瑰瓧鑺�
 * unsigned long rounds 鍔犲瘑杞暟鍙��16鎴�32
 */
char* t_decrypt(const char* encrypt,const char* key,int clen,unsigned int rounds){
char flag[9]="}}}}}}}}";
if(!strncmp(flag,encrypt,8)){
 //int clen= malloc_usable_size((void*)encrypt)-3;
 //printf("clen:%d\n",clen);
 char *content=unflag(encrypt,clen);

 int csize=clen-8;
 //printf("csize:%d\n",csize);
 char* out=(char*)malloc(csize);
 //int klen=strlen(key);
 int i=0;
//ii=0;
 unsigned int v[2];
 unsigned int k[4];
 //if(clen==0||klen==0){
  //free(out);//杩斿洖涓虹┖鍙兘閫犳垚鍐呭瓨娉勬紡
 // free(content);
  //return NULL;
 //}

 validateKey(key,k);
 for(;i<csize-1;i+=8){
  //ii=i;
  v[0]=((content[i]&0x000000FF)<<24)|((content[i+1]&0x000000FF)<<16)|((content[i+2]&0x000000FF)<<8)|(content[i+3]&0x000000FF);
  v[1]=((content[i+4]&0x000000FF)<<24)|((content[i+5]&0x000000FF)<<16)|((content[i+6]&0x000000FF)<<8)|(content[i+7]&0x000000FF);
  inner_decrypt(v,k,rounds);
  //ii=i;
  out[i]  =(char)(v[0]>>24);
  out[i+1]=(char)(v[0]>>16);
  out[i+2]=(char)(v[0]>>8);
  out[i+3]=(char)(v[0]);
  out[i+4]=(char)(v[1]>>24);
  out[i+5]=(char)(v[1]>>16);
  out[i+6]=(char)(v[1]>>8);
  out[i+7]=(char)(v[1]);
 }
out[csize-1]='\0';
free(content);
return out;
}
else {

return NULL;
}
}

char* tea_encry(const char* content,const char* key,unsigned int rounds){
if(content == NULL || key == NULL ||strlen(content) == 0||strlen(key) < 6)//娉ㄦ剰鍒ゆ柇鏉′欢鐨勯『搴忎负NULL闀垮害涓�瀹氫负0 闀垮害涓�0涓嶄竴瀹氫负NULL
     return NULL;
 int len=strlen(content);
 int clen=0;
if(strlen(content)%8==0)
  clen=len+8;
else
  clen = len-len%8+16;
char* en = t_encrypt(content,key,rounds);

  return byte2hex(en,clen);


}


char* tea_decry( char* encrypt,const char* key,unsigned int rounds){
if(encrypt == NULL ||key == NULL ||strlen(encrypt) == 0||strlen(key) < 6 )
     return NULL;
else
  {
 char* out=(char*)malloc((strlen(encrypt)/2+1)*sizeof(char));
  hex2byte(encrypt,out);

const char* out1=out;
char* decrypt_msg = t_decrypt(out1,key,strlen(encrypt)/2+1,rounds);
if(decrypt_msg==NULL)
return NULL;
else
return decrypt_msg;
}
}


