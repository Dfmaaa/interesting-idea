#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 20
#define HASHSET_LEN 1000000

int count_lines(char *fname){

    FILE *fd = fopen(fname, "r");
    int counter=0;
    char char_buff=0;

    while(1){

        char_buff = fgetc(fd);

        if(char_buff == EOF){
            break;
        }

        // next target
        else if(char_buff == '\n'){

            counter++;

        }


    }

    fclose(fd);
    return counter;
}

char ** load_targets(char *fname, int num){

    FILE * fd=fopen(fname,"r");

    char **ret = (char**)malloc(sizeof(char*)*num);

    char char_buff=0;
    int counter = 0;

    for(int i=0;i<num && char_buff != EOF;i++){

        ret[i]=(char*)malloc(sizeof(char)*(MAX_WORD_LEN + 1));

        while(1){

            char_buff = fgetc(fd);

            // end
            if(char_buff == EOF){
                break;
            }

            // next target
            else if(char_buff == '\n'){

                ret[i][counter] = '\0';
                counter = 0;
                break;
            }

            else{
                
                ret[i][counter] = char_buff;

                counter++;

            }


        }


    }
    fclose(fd);
    return ret;

}

void __test_load_targets(char *fname, int num){

    char **rec = load_targets(fname, num);

    for(int i =0; i<num; i++){

        printf("%s\n",rec[i]);

    }

}


char *get_bet(int i, int j, char *str){

    int len=j-i+2; // another 1 for null terminator

    char *ret = (char*)malloc(sizeof(char)*len);

    int counter=0;

    for(int k=i;k<=j;k++){

        ret[counter]=str[k];
        counter++;
        
    }

    ret[counter]='\0';
    return ret;


}
unsigned long hash(const char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash = (unsigned char)c + (hash << 6) + (hash << 16) - hash;
    }
    return hash % HASHSET_LEN;
}


int simple_cmp(char **arr, int num_arr, char *str){

    for(int i=0;i<num_arr;i++ ){

        if(strcmp(arr[i],str)==0){
            return 1;
        }

    }

    return 0;

}

void find(char *source, char *targets, int num_targets){

    char **target_arr=load_targets(targets, num_targets);
    int hashset[HASHSET_LEN],done_hashset[HASHSET_LEN];
    memset(hashset, 0, sizeof(hashset));


    for(int i=0;i<num_targets;i++){
        hashset[hash(target_arr[i])]=1;
    }

    FILE *source_fd = fopen(source, "r");

    char buffer[MAX_WORD_LEN+1];

    char cbuf=0;

    int i1=0; // slider in text

    int ac_count = 0;
    int ac_flag=0;
    int first_flag = 1;
    
    int flag=1;
    
    while(flag){

        i1=0;
        if(first_flag){
            ac_count=0;
        }
        if(first_flag){
        // buffer is loading strings of max size MAX_WORD_LEN from the file after each completion of slide-check algorithm.
        for(int i = 0;i<MAX_WORD_LEN && cbuf != EOF;i++){

            cbuf=fgetc(source_fd);

            if(cbuf == EOF){
                
                flag = 0; 
                break;

            }

            else{

                buffer[i]=cbuf;
                ac_count+=1;

            }



    }
  }     
        else{

            cbuf = fgetc(source_fd);
            if(cbuf == EOF){
                flag = 0;
                break;
            }

            else{

                for(int i =1;i<ac_count;i++){
                    buffer[i-1]=buffer[i];
                }
                buffer[ac_count-1]=cbuf;

            }
        }

        int i2=i1;
        // sliding algorithm that works on buffer array.
        while(i1<ac_count){
            i2=i1;
            for(i1; i2<ac_count; i2++){

                char *str_check=get_bet(i1,i1+i2,buffer);
                if(hashset[hash(str_check)]==1){

                    if(simple_cmp(target_arr,num_targets,str_check)){
                        int h_str = hash(str_check);
                        if(done_hashset[h_str]!=1){
                            done_hashset[h_str]=1;
                            printf("%s found\n", str_check);
                         }
                    }

                }

                free(str_check);   

            }
            i1++;
        }
        first_flag=0;

    }
    fclose(source_fd);


}


int main(int argc, char *argv[]){

    if(argc!=3){
        printf("format: [executable] [source] [targets]\n");
        return -1;
    }

    //__test_load_targets(argv[2],count_lines(argv[2]));
    find(argv[1],argv[2],count_lines(argv[2]));

    return 0;

}