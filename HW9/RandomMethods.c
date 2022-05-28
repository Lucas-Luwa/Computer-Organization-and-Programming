char *replaceCharWithString(char *src1,char src2, char *src3, char *dst);
char *myConcater( char *src1,  char *src2, char *dst);
char *shocker(char *src1);
char *recordPlayer(char *src1, char *scr2);
char *Capitalizer(char *src2);
char *miniConcat(char *src1, char *src2, int s1, int e1, int s2, int e2);
char *indexer(char *src1, char *src2);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main()
{
    char *res;
    printf("Hello World \n");
    // printf("%s,Replace char with string\n",replaceCharWithString("hello",'o',"dingus",res));
    // printf("%s,Personal Concatenator\n",myConcater("yolo","woo",res));
    // printf("%s,Shocker\n", shocker("I LOVE CHEESE"));
    // printf("%s,Shocker\n", shocker("YOLO,WOO"));
    // printf("%s,Noisemaker\n", recordPlayer("Samuel Says: ","MEOW!"));
    printf("%s,LOUDER4PPL->BACK!\n", Capitalizer("I like cheeZe-ItS_A_LoT!! ^_^"));
    printf("%s,BrokenConcat\n",miniConcat("Yo quiero","taco bell",4,9,5,9));
    printf("%s,indexer\n",indexer("gibberihihshmahikerhidinhigushihola","hi"));
    return 0;
}
//struct practice


//Capitalizer
char *Capitalizer(char *string1){
    char *result;
    for(int i = 0;i<strlen(string1)+1;i++){
        if(string1[i]>=97&&string1[i]<=122){
        result[i] = string1[i]-32;
        }else{
        result[i] = string1[i];
        }
    }
    result[strlen(string1)+1] = 0;
    return result;
}
//Search and SPIT VALS.
char *indexer(char *string1,char *string2){
    int *n = calloc(strlen(string1),sizeof(int));
    if(strlen(string2)<=strlen(string1)){
        int indexer = 0;
        for(int j = 0;j<strlen(string1)-strlen(string2);j++){
            int breaker = 1;
            for(int i = 0; i < strlen(string2);i++){
                if(string2[i] != string1[j+i]){
                    breaker = 0;
                }
            }
            if(breaker == 1){
               n[indexer] = j; 
               //printf("%d,,",j);
               indexer++;
            }
        }
    }
    for(int i = 0;i<strlen(string1);i++){
        if(!(i!=0 && n[i]==0)){
            printf("%d, ",n[i]);
        }
    }
    return "YAY!";
}

//Partial Concatenator
char *miniConcat(char *string1, char*string2, int start1, int end1, int start2, int end2){
    char *result = malloc(strlen(string1)+strlen(string2)+100);
    if(start1<0 || start2<0||end1>strlen(string1)||end2>strlen(string2)||end1<start1||end2<start2){
        return "YA DOOFUS YOU SCREWED UP!";
    }
    for(int i = 0; i < end1-start1+1;i++){
        result[i] = string1[i+start1-1];
    }
    for(int j = 0; j < end2-start2+1;j++){
        result[(end1-start1)+j+1] = string2[start2+j-1];
    }
    result[end1-start1+end2-start2+2] = 0;
    return result;
}

//ADD WORD OVER AND OVER
char *recordPlayer(char * string2, char * string3){
    char *string1 = malloc(strlen(string2));
    string1 = realloc(string1, 50);//Ayo i actually did realloc yeyeyeyeyeye.
    //btw string1 gets freed. if no work fix by making new pointer.
    strcpy(string1, string2);
    int chopper = 1;
    int total = strlen(string2)+strlen(string3);
    int j = 0;
    while(chopper == 1){
        
        for(int i = 0; i<25-strlen(string3);i++){
            string1[strlen(string2)+(strlen(string3)*j)+i] = string3[i];
        }
        j++;
        total = total + strlen(string3);
        if(total>50){
            //printf("hi %d",total);
            chopper = 0;
        }
    }
    string1[strlen(string1)] = 0;
    return string1;
}
//ADD !!
char *shocker(char * string2){
    char *string1 = malloc(strlen(string2));
    string1 = realloc(string1, 25);//Ayo i actually did realloc yeyeyeyeyeye.
    //btw string1 gets freed. if no work fix by making new pointer.
    strcpy(string1, string2);
    for(int i = 0; i<25-strlen(string2);i++){
        string1[strlen(string2)+i] = '!';
    }
    string1[strlen(string1)] = 0;
    return string1;
}

//Combiner
char *myConcater(char * string1, char * string2, char * res){
    res = malloc((strlen(string1)+strlen(string2)+1));
    strcpy(res,string1);
    for(int i = 0;i<strlen(string2)+1;i++){
        res[strlen(string1)+i] = string2[i];
    }
    return res;
}
//Method to replace one single char. 
char *replaceCharWithString(char * originalString, char charToReplace, char * stringReplace, char *result) {
  result = malloc(30);
  int length = strlen(stringReplace);
  int k = 0;
  for(int i = 0; i<strlen(originalString); i = i + 1){
    if(originalString[i]==charToReplace){
      for(int j = 0; j<length;j++){
          result[k] = stringReplace[j];
          k++;
      }
    }else{
          result[k] = originalString[i];
          k++;
    }
  }
  result[k] = 0;
  return result;
}
//QUIZ 4
char *returnSomeLetter(char *c);

#include <stdio.h>

int main()
{
    char string[] = "cs2110 is my favorite class";
    char *result = returnSomeLetter(string);
    printf("%s",result);

    return 0;
}
char *returnSomeLetter(char *str){
    char result[4];
    for(int i = 0; i<3;i++){
        result[i] = str[i];
    }
    result[3] = '\0';
    printf("%s",result);
    str = result;
    return str;
}