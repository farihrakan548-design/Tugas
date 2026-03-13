#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Film{
    char name[100];
    double price;
    int year;
    double rating;
};

Film flm[100];
int f = 0;

void loadFile(){
    FILE *file = fopen("netfilm_db.txt","r");

    if(file == NULL) return;
    while(fscanf(file," %[^;];%lf;%d;%lf\n",
        flm[f].name,
        &flm[f].price,
        &flm[f].year,
        &flm[f].rating) != EOF){
        f++;
    }

    fclose(file);
}

void saveFile(){
    FILE *file = fopen("netfilm_db.txt","w");

    for(int i=0;i<f;i++){
        fprintf(file,"%s;%.0lf;%d;%.1lf\n",
        flm[i].name,
        flm[i].price,
        flm[i].year,
        flm[i].rating);
    }

    fclose(file);
}


void tambahFilm(){
	char cari;
	
	cin.ignore();
	do{
    cout<<"Judul : ";
    cin.getline(flm[f].name,100);

    cout<<"Harga : ";
    cin>>flm[f].price;

    cout<<"Tahun : ";
    cin>>flm[f].year;

    cout<<"Rating : ";
    cin>>flm[f].rating;

    f++;
    
	cout<<"Tambah film lagi? (y/n) : ";
    cin>>cari;
    cin.ignore();
    
}while(cari=='y' || cari=='Y');

    saveFile();
}

void tampilFilm(){
    for(int i=0;i<f;i++){
        cout<<"\nFilm "<<i+1<<endl;
        cout<<"Judul  : "<<flm[i].name<<endl;
        cout<<"Harga  : "<<flm[i].price<<endl;
        cout<<"Tahun  : "<<flm[i].year<<endl;
        cout<<"Rating : "<<flm[i].rating<<endl;
    }
}

void bubbleSort(){
    for(int i=0;i<f-1;i++){
        for(int j=0;j<f-i-1;j++){
            if(strcmp(flm[j].name,flm[j+1].name) > 0){
                swap(flm[j],flm[j+1]);
            }
        }
    }
}


int partition(int low,int high){
    double pivot = flm[high].rating;
    int i = low-1;

    for(int j=low;j<high;j++){
        if(flm[j].rating > pivot){
            i++;
            swap(flm[i],flm[j]);
        }
    }

    swap(flm[i+1],flm[high]);
    return i+1;
}

void quickSort(int low,int high){
    if(low < high){
        int pi = partition(low,high);
        quickSort(low,pi-1);
        quickSort(pi+1,high);
    }
}

void linearSearch(char key[]){
    for(int i=0;i<f;i++){
        if(strcmp(flm[i].name,key)==0){
            cout<<"\nFilm ditemukan\n";
            cout<<flm[i].name<<" "<<flm[i].rating<<endl;
            return;
        }
    }
    cout<<"Film tidak ditemukan\n";
}

void binarySearch(char key[]){
    int left=0,right=f-1;

    while(left<=right){
        int mid=(left+right)/2;

        int cmp = strcmp(flm[mid].name,key);

        if(cmp==0){
            cout<<"\nFilm ditemukan\n";
            cout<<flm[mid].name<<" "<<flm[mid].rating<<endl;
            return;
        }
        else if(cmp<0)
            left=mid+1;
        else
            right=mid-1;
    }

    cout<<"Film tidak ditemukan\n";
}

void cariFilm(){
    char key[100];
    cin.ignore();

    cout<<"Masukkan Judul Film : ";
    cin.getline(key,100);

    if(f < 30)
        linearSearch(key);
    else{
        bubbleSort();
        binarySearch(key);
    }
}

int main(){

    int pilih;

    loadFile();

    do{

        cout<<"\n=== LAYARKACA21 DASHBOARD ===\n";
        cout<<"[1] Tambah Film\n";
        cout<<"[2] Tampilkan Film\n";
        cout<<"[3] Sort Judul (Bubble Sort)\n";
        cout<<"[4] Sort Rating (Quick Sort)\n";
        cout<<"[5] Cari Film\n";
        cout<<"[0] Keluar\n";
        cout<<"\n=============================\n";
        cout<<"Pilih Menu : "; cin>>pilih;


        if(pilih==1)
            tambahFilm();

        else if(pilih==2)
            tampilFilm();

        else if(pilih==3){
            bubbleSort();
            tampilFilm();
        }

        else if(pilih==4){
            quickSort(0,f-1);
            tampilFilm();
        }

        else if(pilih==5)
            cariFilm();

    }while(pilih!=0);

}
