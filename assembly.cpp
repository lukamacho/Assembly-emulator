#include <bits/stdc++.h>
#include <fstream>
#include <unistd.h>

using namespace std;

map<string,int> mainData;
map<string,int> functionData;
vector<string> all;
vector<pair<string,int> > chanacvleba;
int arr[1000000];
int SP=1000;
int PC=0;
int RV=0;
int savedPC=0;
bool additional=false;
void gadayevi();
void writeInMemory(string &cur);
void spChange(string &s);
void writeInRegistr(string &s);
void returnValue(string &s);
bool branchebi(string &s);
void loadFromMemory(string & s);
string getRegistr(string s, int index);
int getNumber(string s, int index);
int dasamatebeli(string &s,int &index);
void gadaaxtune(string &s);
void loadFromRegistr(string &s);
void getInstructions();
void welcomeText();
void functionDefinition(string &s, int cur);
void functionCall(string &s);
void writeInMemoryUsingSP(string &s);
void common();
void advancedVersion(bool & morcha);
int main(){
    bool finish=true;
    welcomeText();
    while(finish==true){
        string cur;
        additional=false;
        cout<<"Enter 'common','man','advanced'(for interactive version) or 'exit' if you want to finish working: ";
        cin>>cur;
        if(cur=="exit"){
            break;
        }
        else if(cur=="man"){
            getInstructions();
            continue;
        }
        else if(cur=="common"){
            common();
        }else if(cur=="advanced"){
            additional=true;
            common();
        }
        else{
            cout<<"Enter correct keyword."<<endl;
        }
        cout<<endl;
       
    }
    return 0;
}

void common(){
        string fileAdreess;
        cout<<"Enter file address: ";
        cin>>fileAdreess;
        cout<<endl;
        ifstream file(fileAdreess);
        mainData.clear();
        if(!file){
            cout<<"There is no such file."<<endl;
            cout<<"Please try again."<<endl;
            return;
        }
        all.clear();
        string s;
            while(getline(file,s)){
            all.push_back(s);
            if(s=="main"){
                PC=all.size();
            }
            if(s.substr(0,2)=="fu"){
                functionDefinition(s,all.size());
            }
        }
        gadayevi();
        cout<<"RV="<<RV<<endl;
        cout<<endl;
}
/*This function prints welcome message.*/
void welcomeText(){
    cout<<"Welcome to the assembly emulator!"<<endl;
    cout<<"Before start using this application I advice you to see the instructions and write 'man'."<<endl;
    cout<<"Don't try to lie I, I am very faint and I will be killed in this occasion."<<endl;
}
/*This function gives you any essential information to work well with the program.*/
void getInstructions(){
    cout<<"I have some rules which are down here, and don't dare to break them!"<<endl;
    cout<<"You can use registrs started with 'R' and if you want you can repeat them."<<endl;
    cout<<"I can only use integers don't use short or long."<<endl;
    cout<<"You can use PC to get the instruction line."<<endl;
    cout<<"You can use SP to get information about the stack pointer."<<endl;
    cout<<"You can use RV to write int in the return value."<<endl;
    cout<<"If you want to use memory use M[x] there  'x' is the memory address."<<endl;
    cout<<"I can make four arithmetic operaions:+,-,*,/."<<endl;
    cout<<"You can use standard branch operations but don't forget to write commas after each variable."<<endl;
    cout<<"Here is one example  'BLT 3, 4, PC+20' commas are important."<<endl;
    cout<<"You can jump from lines to lines using unique word 'JMP'."<<endl;
    cout<<"You can call any function by using 'CALL<function>' but you have to define it before."<<endl;
    cout<<"Here is one example 'function<func>' and don't forget to write 'finish' before the end of the funtion."<<endl;
    cout<<"You can only make one of 'ALU' ,'STORE','LOAD' operations on each line. "<<endl;
    cout<<"The main thing is that you are not allowed to use spaces otherwise I maybe crashed."<<endl;
    cout<<"Be careful every keywords are case sensitive!!"<<endl;
    cout<<"If you want to test with your code you can copy it in the 'example.txt' , but don't break rules."<<endl;
    cout<<endl;
}
/*
This function interacts with you if you choose advanced version.
*/
void advancedVersion(bool &morcha){
     string s;
            cout<<"Do you want to get information about SP or PC or Registrs or NOT(if you get bored with it) or 'NOTNOW' : ";
            cin>>s;
            cout<<endl;
            if(s=="YES"){
                cout<<"Choose one of SP,PC, registrs: ";
                string info;
                cin>>info;
                if(info=="SP"){
                    cout<<"SP points to the "<<SP<<" element of an array"<<endl;
                    morcha=true;
                }else if(info=="PC"){
                    cout<<"PC points to the "<<PC<<" line of the file"<<endl;
                    morcha=true;
                }else if(info=="registrs"){
                    bool erti=false;
                    for(auto key: mainData){
                        erti=true;
                        cout<<key.first<<" value is "<<key.second<<endl;
                    }
                    if(erti==false){
                        cout<<"There is no any registr used yet."<<endl;
                    }
                    morcha=true;
                }
            }else if(s=="NOT"){
                additional=false;
            }else if(s=="NOTNOW"){
                morcha=false;
            }
            else{
                cout<<"Enter correct Keyword"<<endl;
                morcha=true;
            }
}
/*
This function parses the whole assembly text 
and divides line by line with appropriate features.
*/
void gadayevi(){
    sleep(1);
    bool morcha=true;
    while(morcha){
        morcha=false;
        if(additional){
           advancedVersion(morcha);
        }
    }
    bool gadaxtoma=false;
    if(PC>=all.size()){
        return;
    }
    string cur=all[PC];
    if(cur=="RET"&&savedPC==0){
        cout<<"The program has finished successfully."<<endl;
        cout<<"The return value is "<<RV<<"."<<endl;
        cout<<endl;
        for(int i=0;i<chanacvleba.size();i++){
            string key=chanacvleba[i].first;
            if(mainData.count(key)!=0){
                mainData[key]=chanacvleba[i].second;
            }
        }
        chanacvleba.clear();
        return;
    }else if(cur=="RET"){
        PC=savedPC;
        savedPC=0;
        cout<<"Funtion calling operation finished successfully."<<endl;
        cout<<endl;
        gadayevi();
        return;
    }
    if(cur[0]=='M'){
       writeInMemory(cur);
    }else if(cur[0]=='R'){
        writeInRegistr(cur);
    }else if(cur[0]=='S'){
        spChange(cur);
    }else if(cur[0]=='B'){
        gadaxtoma=branchebi(cur);
    }else if(cur[0]=='J'){
        gadaaxtune(cur);
        gadayevi();
        return;
    }else if(cur[0]=='C'){
        functionCall(cur);
        return;
    }
    if(gadaxtoma==false){
    PC++;
    }
    gadayevi();
}
/*This function gives one line of string and stores information in memory.*/
void writeInMemory(string & s){
    int size=0;
    int index=2;
    if(s[2]=='R'){
        string registr="";
        while(s[index]!=']'){
            registr+=s[index];
            index++;
        }
        int chasaweri=mainData[registr];
        index+=2;
        int first=0;
        int second=0;
        string aqamde="";
        while(s[index]!='+'&&s[index]!='-'){
            aqamde+=s[index];
            index++;
            if(index==s.size()){
                break;
            }
        }
        if(aqamde[0]=='R'){
            //cout<<aqamde<<"esaa "<<mainData[aqamde]<<endl;
            first=mainData[aqamde];
        }else{
            first=stoi(aqamde);
        }
        if(index==s.size()){
            arr[chasaweri]=first;
            cout<<"Successfully stored information in the memory."<<endl;
            cout<<first<<" was written on the "<< chasaweri << " index of the array."<<endl;
            cout<<endl;
            return;
        }
        bool mimateba=true;
        if(s[index]=='-'){
            mimateba=false;
        }
        index++;
        string darchenili=s.substr(index);
        if(darchenili[0]=='R'){
            second=mainData[darchenili];
        }else{
            second=stoi(darchenili);
        }
        int answer=first;
        if(mimateba){
            answer+=second;
        }else{
            answer-=second;
        }
        cout<<"Successfully stored information in the memory."<<endl;
        cout<<answer<<" was written on the "<< chasaweri << " index of the array."<<endl;
        cout<<endl;
        arr[chasaweri]=answer;
    }else{
        writeInMemoryUsingSP(s);
    }
}
/*This operation changes the Stack Pointer.*/
void spChange(string &s){
    int pliusMinusi=0;
    int index=2;
    while(s[index]!='='){
        if(s[index]=='+'){
            pliusMinusi=1;
        }else if(s[index]=='-'){
            pliusMinusi=2;
        }
        index++;
    }
    if(pliusMinusi==1){
        int das=0;
        if(s[index+1]=='R'){
           das+=mainData[s.substr(index+1)];     
        }else{
            das=stoi(s.substr(index+1));
        }
        SP+=das/4;
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
        return;
    }else if(pliusMinusi==2){
        int das=0;
        if(s[index+1]=='R'){
           das+=mainData[s.substr(index+1)];     
        }else{
            das=stoi(s.substr(index+1));
        }
        SP-=das/4;
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
        return;
    }
    index++;
    if(s[index]=='S'){
        int das=stoi(s.substr(index+3));
        if(s[index+2]=='-'){
            SP-=das/4;
        }else{
            SP+=das/4;
        }
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
        return;
    }
    string key=s.substr(index,2);
    if(index+2==s.size()){
        SP=mainData[key]/4;
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
        return;
    }
    int das=mainData[key];
    int meore=stoi(s.substr(index+3));
    if(s[index+1]=='-'){
        SP=(das-meore)/4;
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
        return;
    }else{
        SP=(das+meore)/4;
        cout<<"Successfully changed stack pointer location."<<endl;
        cout<<"Now it points to the "<<SP<<" element of an array."<<endl;
        cout<<endl;
    }
}
/*
This is helper function and returns the number to write in registr or in memory.
*/
int dasamatebeli(string &s, int &index){
            int first=0;
            if(s[index]=='R'){
                string registr="";
                while(s[index]!='-'&&s[index]!='+'&&s[index]!='/'&&s[index]!='*'){
                    registr+=s[index];
                    index++;
                    if(index==s.size()){
                        break;
                    }
                }
                if(registr=="RV"){
                    first=RV;
                    return first;
                }
                first=mainData[registr];
            }else{
               string number="";
                while(s[index]!='-'&&s[index]!='+'&&s[index]!='/'&&s[index]!='*'){
                    number+=s[index];
                    index++;
                    if(index==s.size()){
                        break;
                    }
                }
                first=stoi(number); 
            }
    return first;
}
/*This function makes Arithmetic Logical Unit instructions.*/
void writeInRegistr(string & s){
        string dam=s.substr(0,2);
        /*If this is return value write in it.*/
        if(dam=="RV"){
            returnValue(s);
            return;
        } string cur=s;
        bool arithmetic=false;
        for(int i=0;i<cur.size();i++){
             if(cur[i]=='+'||cur[i]=='-'||cur[i]=='*'||cur[i]=='/'){
                arithmetic=true;
            }
        }
        int index=0;
        while(s[index]!='='){
            index++;
        }
        dam=s.substr(0,index);
        index++;
        bool mimateba=true;
        if(s[index]=='M'){
            loadFromMemory(s);
            return;
        }else if(arithmetic==false){
            loadFromRegistr(s);
           return;
        }
        else if(s[index]=='S'){
            if(index+2==s.size()){
                mainData[dam]=SP;
                return;
            }
            if(s[index+2]=='-'){
                mimateba=false;
            }
            int answer=0;
            int das=stoi(s.substr(index+3));
            if(mimateba){
                answer=SP+(das/4);
            }else{
                answer=SP-(das/4);
            }
            mainData[dam]=answer;
            cout<<"Succesfully performed load operation."<<endl;
            cout<<answer<<" was loaded in"<<dam<<" registr."<<endl;
            cout<<endl;
        }else{
            int answer=0;
            int first=0;
            int second=0;
            first=dasamatebeli(s,index);
            if(index==s.size()){
                mainData[dam]=first;
                cout<<"Load operation performed succesfully."<<endl;
                cout<<first<<" was loaded in "<<dam<<endl;
                cout<<endl;
                cout<<"ds"<<endl;
                return;
            }
            int operacia=0;
            if(s[index]=='+'){
                operacia=1;
            }else if(s[index]=='-'){
                operacia=2;
            }else if(s[index]=='*'){
                operacia=3;
            }else if(s[index]=='/'){
                operacia=4;
            }
            index++;
            second=dasamatebeli(s,index);
            if(operacia==1){
                mainData[dam]=(first+second);
            }else if(operacia==2){
                mainData[dam]=(first-second);
            }else if(operacia==3){
                mainData[dam]=first*second;
            }else {
                mainData[dam]=(int)(first/second);
            }
        }
        cout<<"ALU operation performed successfully."<<endl;
        cout<<dam<<" registr is equal to "<<mainData[dam]<<endl;
        cout<<endl;
}
/*Writes an int in the RV "return value" .*/
void returnValue(string &s){
    int index=3;
    int answer;
    int first=0;
    int second=0;
    if(s[index]=='M'){
        string registr="";
        index+=2;
        while(s[index]!=']'){
            registr+=s[index];
            index++;
        }
        int answer;
        if(registr[0]=='R'){
        answer=arr[mainData[registr]];
        }else if(registr[0]=='S'){
        answer=arr[SP];
        }
        RV=answer;
        cout<<"Succesfully performed load operation in the return value."<<endl;
        cout<<answer<<" was loaded in the return value."<<endl; 
        cout<<endl;
        return;
    }
    string axla="";
    while(s[index]!='*'&&s[index]!='+'&&s[index]!='/'&&s[index]!='-'&&index<s.size()){
        axla+=s[index];
        index++;
    }
    if(axla[0]=='R'){
        first=mainData[axla];
    }else{
        first=stoi(axla);
    }
    if(index==s.size()){
        RV=first;
        cout<<"Succesfully performed load operation in the return value."<<endl;
        cout<<first<<" was loaded in the return value."<<endl; 
        cout<<endl;
        return;
    }
    int operation=0;
    if(s[index]=='+'){
        operation=1;
    }else if(s[index]=='-'){
        operation=2;
    }else if(s[index]=='*'){
        operation=3;
    }else{
        operation=4;
    }
    string meore=s.substr(index+1);
    if(meore[0]=='R'){
        second=mainData[meore];
    }else{
        second=stoi(meore);
    }
    if(operation==1){
        answer=first+second;
    }else if(operation==2){
        answer=first-second;
    }else if(operation==3){
        answer=first*second;
    }else{
        answer=(int)first/second;
    }
    RV=answer;
    cout<<"Succesfully performed load operation in the return value."<<endl;
    cout<<answer<<" was loaded in the return value."<<endl; 
    cout<<endl;
}

/*This function makes branc operation.*/
bool branchebi(string &s){
    string cur=s.substr(0,3);
    int index=3;
    while(s[index]==' '){
        index++;
    }
    int first=0;
    int second=0;
    if(s[index]=='R'){
        string registr=getRegistr(s,index);
        //cout<<registr<<endl;
        first=mainData[registr];
    }else if(s[index]!='R'){
        first=getNumber(s,index);
    }
    while(s[index]!=' '){
        index++;
    }while(s[index]==' '){
        index++;
    }

    if(s[index]=='R'){
        string registr=getRegistr(s,index);
        second=mainData[registr];
    }else if(s[index]!='R'){
        second=getNumber(s,index);
    }
    bool answer=false;
    if((cur=="BEQ"&&first==second)||(cur=="BLT"&&first<second)
    ||(cur=="BLE"&&first<=second)||(cur=="BGT"&&first>second)||
    (cur=="BGE"&&first>=second||(cur=="BNE"&&first!=second))){
        answer=true;
    }
    if(answer){
        while(s[index]!=' '){
            index++;
        }while(s[index]==' '){
            index++;
        }
        if(s[index]!='P'){
            string last=s.substr(index);
            PC=(int)stoi(last)/4;
        }else{
            index+=2;
            bool mimateba=true;
            if(s[index]=='-'){
                mimateba=false;
            }
            index++;
            int number=stoi(s.substr(index))/4;
            if(mimateba){
                PC+=number;
            }else{
                PC-=number;
            }
        }
   }
    return answer;
}
/*
This function return the string of registr.
*/
string getRegistr(string s, int index){
    string cur="";
    while(s[index]!=','){
        cur+=s[index];
        index++;
    }
    return cur;
}
/*This function returns the int number which appropriates the given string.*/
int getNumber(string s, int index){
    string cur="";
    while(s[index]!=','){
        cur+=s[index];
        index++;
    }
    return stoi(cur);
}

/*This function makes assembly jump operation.*/
void gadaaxtune(string &s){
    int index=3;
    while(s[index]==' '){
        index++;
    }
    if(s[index]=='P'){
        bool mimateba=true;
        index+=2;
        if(s[index]=='-'){
            mimateba=false;
        }
        int add=0;
        index++;
        if(s[index]!='R'){
            add=(int)stoi(s.substr(index))/4;
        }else{
            string registr=s.substr(index);
            add=(int)mainData[registr]/4;
        }
        if(mimateba){
            PC+=add;
        }else{
            PC-=add;
        }
        cout<<"Successfully made jump operation"<<endl;
        cout<<"Now PC is on "<<PC<<" line."<<endl;
        cout<<endl;
    }else{
        int add=0;
        if(s[index!='R']){
        add=stoi(s.substr(index));
        }else{
            string registr=s.substr(index);
            add=mainData[registr];
        }
        PC=(int)add/4;
        cout<<"Successfully made jump operation"<<endl;
        cout<<"Now PC is on "<<PC<<" line."<<endl;
        cout<<endl;
    }
   // cout<<PC<<endl;
}

/*This function makes load operation.*/
void loadFromMemory(string &s){
    string registr="";
    int index=0;
    while(s[index]!='='){
        registr+=s[index];
        index++;
    }
    index+=3;
    if(s[index]=='R'){
        string meore="";
        while(s[index]!=']'){
            meore+=s[index];
            index++;
        }
        int answer=arr[mainData[meore]];
        mainData[registr]=answer;
        cout<<"Succesfully performed load operation."<<endl;
        cout<<answer<<" was loaded in "<<registr<<"."<<endl;
        return;
    }else if(s[index]=='S'){
        if(s.size()<=index+3){
           mainData[registr]=arr[SP]; 
           cout<<"Succesfully performed load operation."<<endl;
           cout<<arr[SP]<<" was loaded in "<<registr<<"."<<endl;
           cout<<endl;
           return;
        }
        bool mimateba=true;
        if(s[index+2]=='-'){
            mimateba=false;
        }
        string next="";
        index+=3;
        while(s[index]!=']'){
            next+=s[index];
            index++;
        }
        int das=0;
        if(next[0]=='R'){
            das=mainData[next];
        }else{
            das=stoi(next);
        }
        int amosaweri=SP;
        if(mimateba){
            amosaweri+=(das/4);
        }else{
            amosaweri-=(das/4);
        }
        mainData[registr]=arr[amosaweri];
        cout<<"Succesfully performed load operation."<<endl;
        cout<<arr[amosaweri]<<" was loaded in "<<registr<<"."<<endl;
        cout<<endl;
    }
}

/*
This function allows us to load information from registr.
*/
void loadFromRegistr(string &s){
    string registr="";
    int index=0;
    while(s[index]!='='){
        registr+=s[index];
        index++;
    }
    index++;
    int value;
    if(s[index]=='R'){
        string chasaweri=s.substr(index);
        if(chasaweri=="RV"){
            value=RV;
        }else{
        value=mainData[chasaweri];
        }
    }else if(s[index]=='S'){
        value=SP;
    }else{
        string left=s.substr(index);
        value=stoi(left);
    }
    mainData[registr]=value;

    cout<<"Succesfully performed load operation."<<endl;
    cout<<value<<"  was loaded into "<<registr<<"."<<endl;
    cout<<endl;
}
/*
After parsing line this function stores information about the starting line of the function.
*/
void functionDefinition(string &s, int cur){
    string functionName="";
    int index=0;
    while(s[index]!='<'){
        index++;
    }
    index++;
    while(s[index]!='>'){
        functionName+=s[index];
        index++;
    }
    functionData[functionName]=cur;
    //cout<<functionName<<" "<<cur-1<<endl;
}

/*
This function will call the function and points PC to its address.
*/
void functionCall(string &s){
    string name="";
    int index=0;
    while(s[index]!='<'){
        index++;
    }
    index++;
    while(s[index]!='>'){
        name+=s[index];
        index++;
    }
    savedPC=PC+1;
    PC=functionData[name];
    for(auto key: mainData){
        chanacvleba.push_back({key.first,key.second});
    }
    cout<<"calling "<<name<<" function."<<endl;
    gadayevi();
}

/*
This function gives us an opportunity to write in memory by using SP.
*/
void writeInMemoryUsingSP(string &s){
    int chasaweri=SP;
    int index=4;
    int operacia=0;
    //cout<<s[index]<<endl;
    if(s[index]==']'){
        operacia=0;
    }else if(s[index]=='+'){
        operacia=1;
    }else if(s[index]=='-'){
        operacia=2;
    }else if(s[index]=='*'){
        operacia=3;
    }else if(s[index]=='/'){
        operacia=4;
    }
    int misamatebeli=0;
    if(operacia!=0){
        index++;
        string number="";
        while(s[index]!=']'){
            number+=s[index];
            index++;
        }
        int damateba=stoi(number);
        if(operacia!=0){
            if(operacia==1){
                chasaweri+=(damateba/4);
            }if(operacia==2){
                chasaweri-=(damateba/4);
            }if(operacia==3){
                chasaweri*=damateba;
            }if(operacia==4){
                chasaweri=(int)(chasaweri/damateba);
            }
        }
    }
    int ricxvi;
    index+=2;
    string left=s.substr(index);
    if(left[0]!='R'){
        ricxvi=stoi(left);
    }else{
        ricxvi=mainData[left];
    }
    arr[chasaweri]=ricxvi;
    cout<<"Successfully performed store information."<<endl;
    cout<<ricxvi<<" was written on the "<<chasaweri<<" index of an array."<<endl;
    cout<<endl;
}