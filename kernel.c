void printString(char*);
void readString(char*);
int DIV(int,int);
int MOD(int,int);
void readSector(char*,int);
void handleInterrupt21(int,int,int,int);





main(){
  char buffer[512];
  readSector(buffer, 30);
  printString(buffer);

  while(1);

}

void printString(char* text){
  int i = 0;
  while(1){
    char x = text[i];
    if(x != '\0')
  interrupt(0x10,0xE*256+text[i],0,0,0);
  else
  break;
  i = i +1;
}
}

void readString(char* text){

  char element='c';
  int i =1;
  text[0] = 0xa;
while(1){
  element = interrupt(0x16,0,0,0,0);
  interrupt(0x10,0xE*256+element,0,0,0);
  if(element==0xd){
    text[i] = 0xa;
    i=i+1;
    text[i] = 0x0;
    break;

  }else{    // other than enter
    if(element==0x8){  // backspace case
      if(i==1){  // start of line backspace case
        printString(" ");
      }
      else{ // normal backspace
        i=i-1;
      }
    }
    else{ //entering the element
      text[i] = element;
      i = i+1;

    }
  }
}
}

int DIV(int a,int b){
  int result=0;
  while(a>=b){
    result=result+1;
    a=a-b;
  }
  return result;
}

int MOD(int a ,int b){
  int result=0;
  int temp = DIV(a,b);
  int temp2 = temp*b;
  result=a-temp2 ;
  return result;
}


void readSector(char* buffer, int sector){
    int temp = MOD(sector,18);
    int rsector = temp+1;

     int temp2 = DIV(sector,18);

    int head = MOD(temp2,2);

    int track = DIV(sector,36);

    int ax= 2*256+1;

    int bx=buffer;

    int cx= track*256+rsector;

    int dx=head*256+0;

    interrupt(0x13,ax,bx,cx,dx);





    

}

void handleInterrupt21(int ax, int bx, int cx, int dx){
  if(ax==0){
    printString(bx);
  }else if (ax==1){
    readString(bx);
  }else if(ax==2){
    readSector(bx,cx);
  }else{
    printString("Error 404");
  }

}
