
char* mystrcpy(char *_Destination, const char *_Source){
    int str_end = 0;
    int i=0;
    while(!str_end){
        *(_Destination+i)=*(_Source+i);
        if(*(_Source+i)=='\0'){
            str_end=1;
        }
        i++;
    }
    return _Destination;
}
void mystrcpy2(char *_Destination, const char *_Source){
    //here i want to a shorter way with incrementation + assignment notation : var++
    int str_end = 0;
    while(!str_end){
        if(*(_Source)=='\0')
            str_end=1;
        *(_Destination++)=*(_Source++);     
    }
    return;
}


char* mystrcat(char *_Destination, const char *_Source){
    int str_end = 0;
    int j,i=0;
    while(!str_end){
        if(*(_Destination+i)=='\0'){
            str_end=1;
            j=i;
        }
        else{
            i++;
        }    
    }
    i=0;
    str_end = 0;
    while(!str_end){
        *(_Destination+j+i)=*(_Source+i);
        if(*(_Source+i)=='\0'){
            str_end=1;
        }
        i++;
    }
    return _Destination;
}

void mystrcat2(char *_Destination, const char *_Source){
    //here i want to a shorter way with incrementation + assignment notation : var++
    int str_end = 0;
    while(!str_end){
        if(*(_Destination)=='\0'){
            str_end=1;
        }
        else{
            _Destination++;
        }
    }
    str_end = 0;
    while(!str_end){
        if(*(_Source)=='\0'){
            str_end=1;
        }
        *(_Destination++)=*(_Source++);     
    }
    return;
}

unsigned long long mystrlen(const char *_Str){
    unsigned long long i = 0;
    int str_end=0;
    while(!str_end){
        if(*(_Str+i)=='\0'){
            str_end=1;
        }
        else{
            i++;
        }
    }
    return i;
}

int mystrcmp(const char *_Str1, const char *_Str2){
    //i discovered on forums that *_Stri1 its the same of *_Str1 != '\0' and also str2!='\0' no needed if Str1!=str2 !
    while (*_Str1 && (*_Str1 == *_Str2)) { 
        _Str1++;
        _Str2++;
    }//i used string_ponter++ ,the alternative was to use i counter *(string_pointer+i)
    return (unsigned char)*_Str1 - (unsigned char)*_Str2 ;
}