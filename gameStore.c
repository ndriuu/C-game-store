#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
//=============
void admin();
void addAdmin();
void loginAdmin();
void berandaAdmin();
void listGameAdmin();
void accRefund();
void deleteGameAdmin();
void findAccountAdmin();
//=============
void penjual();
void addPenjual();
void loginPenjual();
void berandaPenjual();
void uploadGamePenjual();
void accOrder();
//=============
void pembeli();
void addPembeli();
void loginPembeli();
void berandaPembeli();
void buyGame();
void fillBalance();
void refundGame();
void buyingHistory();
//=============
struct{
	char username[50], password[50], role[10];
	int saldo;
}dataUser;
struct{
	char username[50], password[50], role[10];
	int saldo;
}session_dataUser;
struct{
	char username[50],namaGame[50];
	int hargaGame, stokGame;
}dataGame;
struct{
	char username[50],namaGame[50];
	int hargaGame, stokGame;
}dataGame_list[50],temp;
struct{
	char username_penjual[50],username_pembeli[50],namaGame[50];
	int hargaGame, stokGame,totalHarga,kodePembelian,statusPembelian;
}buyingData;
struct{
	char username_penjual[50],username_pembeli[50],namaGame[50];
	int hargaGame, stokGame,totalHarga,kodePembelian,statusPembelian;
}buyingData_list;
int status_login,status_delete,status_find,status_buyingData,status_fillBalance,status_refund;
//=============================== Start
int main(){
	int pilihan;
	printf("====Welcome====\n");
	printf("1. Admin\n2. Penjual\n3. Pembeli\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");admin();break;
		case 2 	: system("cls");penjual();break;
		case 3 	: system("cls");pembeli();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");main();
	}
}
//=============================== Admin
void admin(){
	int pilihan;
	printf("====Menu Admin====\n");
	printf("1. Sign UP\n2. Login\n3. Kembali\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");addAdmin();system("pause");system("cls");main();break;
		case 2 	: system("cls");loginAdmin();break;
		case 3 	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");admin();
	}
}
void addAdmin(){
	printf("====Tambah Admin====\n");
    printf("Username\t: ");
    gets(dataUser.username);
    printf("Password\t: ");
    gets(dataUser.password);
    strcpy(dataUser.role, "Admin");
    dataUser.saldo = 0;
    //=================
    FILE *f_addAccount;
    f_addAccount = fopen("dataUser.dat","ab");
    fwrite(&dataUser,sizeof(dataUser),1,f_addAccount);
    fclose(f_addAccount);
    //=================
}
void loginAdmin(){
	char username[50],password[50];
    printf("====Login Admin====\n");
    printf("Username\t: ");
    gets(username);
    printf("Password\t: ");
    gets(password);
    //==================
    FILE *f_getAccount;
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
    	//printf("Data Username : %s\n",dataUser.username);
    	if(strcmp(username,dataUser.username)==0 && strcmp(password,dataUser.password)==0 && strcmp(dataUser.role,"Admin")==0){
    		status_login = 1;
    		strcpy(session_dataUser.username,dataUser.username);
    		strcpy(session_dataUser.password,dataUser.password);
    		strcpy(session_dataUser.role,dataUser.role);
    		session_dataUser.saldo = dataUser.saldo;
			break;
		}else{
			status_login = 0;
		}
    }
    fclose(f_getAccount);
    if(status_login == 1){
    	printf("\n====Login Success====\n\n");
    	system("pause");
		system("cls");
		berandaAdmin();
	}else if(status_login == 0){
		printf("\n====Username or Password is invalid====");
		printf("\n\n");
		system("pause");
		system("cls");
		loginAdmin();
	}else{
		printf("\n====System Error====\n");
		exit(0);
	}
}
void berandaAdmin(){
	int pilihan;
	printf("====Menu Aksi====\n");
	printf("1. List Game\n2. Acc Refund\n3. Delete Game\n4. Find Account\n5. Logout\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");listGameAdmin();system("pause");system("cls");berandaAdmin();break;
		case 2 	: system("cls");accRefund();system("pause");system("cls");berandaAdmin();break;
		case 3 	: system("cls");deleteGameAdmin();system("pause");system("cls");berandaAdmin();break;
		case 4 	: system("cls");findAccountAdmin();system("pause");system("cls");berandaAdmin();break;
		case 5 	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");berandaAdmin();
	}
}
void listGameAdmin(){
	FILE *f_getDataGame;
	printf("====Data Game====\n");
    int n=0,i,j;
    f_getDataGame = fopen("dataGame.dat","rb");
    while(fread(&dataGame,sizeof(dataGame),1,f_getDataGame)==1){
    	strcpy(dataGame_list[n].username,dataGame.username);
    	strcpy(dataGame_list[n].namaGame,dataGame.namaGame);
    	dataGame_list[n].hargaGame = dataGame.hargaGame;
    	dataGame_list[n].stokGame = dataGame.stokGame;
    	n++;
    }
    fclose(f_getDataGame);
	for (i = 0; i<n; i++){
	    for (j = 0; j < n; j++){
	        if (strcmp(dataGame_list[j-1].namaGame , dataGame_list[j].namaGame) >=0) 
	        {
	            temp =dataGame_list[j-1]; 
	            dataGame_list[j - 1] = dataGame_list[j];
	            dataGame_list[j] = temp;
	        }
	    }
	}
	for (i = 0; i < n ; i++){
	    printf("%d. Nama Game\t: %s\n",i+1, dataGame_list[i].namaGame);
	    printf("   Username \t: %s\n",dataGame_list[i].username);
	    printf("   Harga\t: %d\n", dataGame_list[i].hargaGame);
	    printf("   stok\t\t: %d\n", dataGame_list[i].stokGame);
    }
}
void accRefund(){
	FILE *f_getAccount;
	printf("====Data Pembelian====\n");
    int i=1;
    f_getAccount = fopen("dataPembelian.dat","rb");
    //printf("%s",session_dataUser.username);
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
    	//printf("%s",session_dataUser.role);
    	if(buyingData.statusPembelian == 2){
	    	printf("%d. ",i);
	        printf("Kode\t\t: %d\n", buyingData.kodePembelian);
	        printf("   Penjual \t: %s\n", buyingData.username_penjual);
	        printf("   Pembeli \t: %s\n", buyingData.username_pembeli);
	        printf("   Nama Game\t: %s\n", buyingData.namaGame);
	        printf("   Harga\t: %d\n", buyingData.hargaGame);
	        printf("   stok\t\t: %d\n", buyingData.stokGame);
	        printf("   Total Harga\t: %d\n", buyingData.totalHarga);
			printf("   Status\t: %d\n", buyingData.statusPembelian);
	        i++;
	        printf("\n");
		}

    }
    fclose(f_getAccount);
    int kodePembelian;
    printf("Kode data yang akan di Acc : ");
    scanf("%d",&kodePembelian);
	FILE *f_struktur;
	FILE *f_struktur_1;
    f_struktur=fopen("dataPembelian.dat","rb");
    f_struktur_1=fopen("dataPembelian_temp.dat","wb");
    //printf("Jumlah Stok : %d",buyingData.stokGame);
    while(fread(&buyingData,sizeof(buyingData),1,f_struktur)==1){
        if(kodePembelian == buyingData.kodePembelian){
        	strcpy(buyingData_list.username_penjual,buyingData.username_penjual);
    		strcpy(buyingData_list.username_pembeli,buyingData.username_pembeli);
    		strcpy(buyingData_list.namaGame,buyingData.namaGame);
			buyingData_list.hargaGame = buyingData.hargaGame;
			buyingData_list.stokGame = buyingData.stokGame;
			buyingData_list.totalHarga = buyingData.totalHarga;
			buyingData_list.kodePembelian = buyingData.kodePembelian;
        	buyingData_list.statusPembelian = buyingData.statusPembelian = 3;
        }
        fwrite(&buyingData,sizeof(buyingData),1,f_struktur_1);
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataPembelian.dat");
    rename("dataPembelian_temp.dat","dataPembelian.dat");
    if(buyingData_list.statusPembelian==3){
	    f_struktur=fopen("dataUser.dat","rb");
		f_struktur_1=fopen("dataUser_temp.dat","wb");
		//printf("Jumlah Stok : %d",buyingData.stokGame);
		while(fread(&dataUser,sizeof(dataUser),1,f_struktur)==1){
		    if(strcmp(buyingData_list.username_penjual,dataUser.username)==0 && strcmp(dataUser.role,"Penjual")==0){
		    	dataUser.saldo -= buyingData_list.totalHarga;
		    }
		    if(strcmp(buyingData_list.username_pembeli,dataUser.username)==0 && strcmp(dataUser.role,"Pembeli")==0){
		    	dataUser.saldo += buyingData_list.totalHarga;
			}
		    fwrite(&dataUser,sizeof(dataUser),1,f_struktur_1);
		}
		fclose(f_struktur);
		fclose(f_struktur_1);
		remove("dataUser.dat");
		rename("dataUser_temp.dat","dataUser.dat");
		//=====================================
		f_struktur=fopen("dataGame.dat","rb");
	    f_struktur_1=fopen("dataGame_temp.dat","wb");
	    //printf("Jumlah Stok : %d",buyingData.stokGame);
	    while(fread(&dataGame,sizeof(dataGame),1,f_struktur)==1){
	        if(strcmp(buyingData_list.namaGame,dataGame.namaGame)==0){
	        	dataGame.stokGame += buyingData_list.stokGame;
	        }
	        fwrite(&dataGame,sizeof(dataGame),1,f_struktur_1);
	    }
	    fclose(f_struktur);
	    fclose(f_struktur_1);
	    remove("dataGame.dat");
	    rename("dataGame_temp.dat","dataGame.dat");
	    printf("\n\n====Acc Refund Berhasil====\n\n");
	}else{
		printf("\n====Kode data tidak ditemukan====\n\n");
	}
}
void deleteGameAdmin(){
	char target[50];
	listGameAdmin();
	FILE *f_struktur;
	FILE *f_struktur_1;
    printf("Masukan Nama Game yang akan dihapus : ");
    gets(target);
    f_struktur=fopen("dataGame.dat","rb");
    f_struktur_1=fopen("dataGame_temp.dat","wb");
    status_delete = 0;
    while(fread(&dataGame,sizeof(dataGame),1,f_struktur)==1){
        if(strcmp(dataGame.namaGame,target)!=0){
            fwrite(&dataGame,sizeof(dataGame),1,f_struktur_1);
        }else{
        	status_delete = 1;
		}
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataGame.dat");
    rename("dataGame_temp.dat","dataGame.dat");
    if(status_delete == 1){
    	printf("\n====Data berhasil dihapus====\n");
	}else{
		printf("\n====Data tidak ditemukan====\n\n");
	}
}
void findAccountAdmin(){
	printf("====Data Akun====\n");
    FILE *f_getAccount;
    int i=1;
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
        if(strcmp(dataUser.role,"Admin")==0){
			continue;	
        }
        printf("%d. ",i);
        printf("Username \t: %s\n", dataUser.username);
        printf("   Saldo\t: %d\n", dataUser.saldo);
        printf("   Role\t\t: %s\n", dataUser.role);
        i++;
    }
    fclose(f_getAccount);
	f_getAccount = fopen("dataUser.dat","rb");
	char target[50];
    printf("Masukan Nama Game yang akan dicari : ");
	gets(target);
	printf("====Hasil Pencarian====\n");
	status_find = 0;
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
	    if(strcmp(dataUser.username,target)==0){
	    printf("   Username \t: %s\n", dataUser.username);
	    printf("   Saldo\t: %d\n", dataUser.saldo);
	    printf("   Role\t\t: %s\n", dataUser.role);	
	    status_find = 1;
	    }
    }
    if(status_find == 0){
    	printf("\n  Data tidak ditemukan\n\n");
	}
    fclose(f_getAccount);

}
//=============================== Penjual
void penjual(){
	int pilihan;
	printf("====Menu Penjual====\n");
	printf("1. Sign UP\n2. Login\n3. Kembali\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");addPenjual();system("pause");system("cls");penjual();break;
		case 2 	: system("cls");loginPenjual();break;
		case 3 	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");penjual();
	}
}
void addPenjual(){
	printf("====Tambah Penjual====\n");
    printf("Username\t: ");
    gets(dataUser.username);
    printf("Password\t: ");
    gets(dataUser.password);
    strcpy(dataUser.role, "Penjual");
    dataUser.saldo = 0;
    //=================
    FILE *f_addAccount;
    f_addAccount = fopen("dataUser.dat","ab");
    fwrite(&dataUser,sizeof(dataUser),1,f_addAccount);
    fclose(f_addAccount);
    //=================
}
void loginPenjual(){
	int percobaan_penjual = 3;
	char username[50],password[50];
	back:
	if(percobaan_penjual == 0){
		system("cls");
		main();
	}
    printf("Kesempatan Login : %d\n",percobaan_penjual);
    printf("====Login Penjual====\n");
    printf("Username\t: ");
    gets(username);
    printf("Password\t: ");
    gets(password);
    //==================
    FILE *f_getAccount;
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
    	if(strcmp(username,dataUser.username)==0 && strcmp(password,dataUser.password)==0 && strcmp(dataUser.role,"Penjual")==0){
    		status_login = 1;
    		strcpy(session_dataUser.username,dataUser.username);
    		strcpy(session_dataUser.password,dataUser.password);
    		strcpy(session_dataUser.role,dataUser.role);
			session_dataUser.saldo = dataUser.saldo;			
			break;
		}else{
			status_login = 0;
		}
    }
    fclose(f_getAccount);
    //printf("status_login : %d\n",status_login);
    if(status_login == 1){
    	printf("\n====Login Success====\n\n");
    	system("pause");
		system("cls");
    	berandaPenjual();
    	
	}else if(status_login == 0){
		printf("\n====Username or Password is invalid====");
		printf("\n\n");
		percobaan_penjual--;
		system("pause");
		system("cls");
		goto back;
	}else{
		printf("\n====System Error====\n");
		main();
	}
}
void berandaPenjual(){
	int pilihan;
	FILE *f_getAccount;
	printf("====Data Penjual====\n");
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
    	if(strcmp(session_dataUser.username,dataUser.username)==0 && strcmp(session_dataUser.role,"Penjual")==0){
			printf("Username \t: %s\n", dataUser.username);
	        printf("Saldo\t\t: %d\n", dataUser.saldo);
	        break;
        }
    }
    fclose(f_getAccount);
	printf("====Menu Aksi====\n");
	printf("1. Upload Game\n2. Acc Order\n3. Logout\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");uploadGamePenjual();system("pause");system("cls");berandaPenjual();break;
		case 2 	: system("cls");accOrder();system("pause");system("cls");berandaPenjual();break;
		case 3 	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");berandaPenjual();
	}
}
void uploadGamePenjual(){
	printf("====Upload Game====\n");
	strcpy(dataGame.username,session_dataUser.username);
    printf("Nama Game\t: ");
    gets(dataGame.namaGame);
    printf("Harga\t\t: ");
    scanf("%d",&dataGame.hargaGame);getchar();
    printf("Stok\t\t: ");
    scanf("%d",&dataGame.stokGame);getchar();
    //=================
    FILE *f_uploadGame;
    f_uploadGame = fopen("dataGame.dat","ab");
    fwrite(&dataGame,sizeof(dataGame),1,f_uploadGame);
    fclose(f_uploadGame);
    system("pause");
	system("cls");
    berandaPenjual();
}
void accOrder(){
	FILE *f_getAccount;
	printf("====Data Pembelian====\n");
    int i=1;
    f_getAccount = fopen("dataPembelian.dat","rb");
    //printf("%s",session_dataUser.username);
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
    	//printf("%s",session_dataUser.role);
    	if(strcmp(buyingData.username_penjual,session_dataUser.username)==0 && strcmp(session_dataUser.role,"Penjual")==0 && buyingData.statusPembelian == 0){
	    	printf("%d. ",i);
	        printf("Kode\t\t: %d\n", buyingData.kodePembelian);
	        printf("   Penjual \t: %s\n", buyingData.username_penjual);
	        printf("   Pembeli \t: %s\n", buyingData.username_pembeli);
	        printf("   Nama Game\t: %s\n", buyingData.namaGame);
	        printf("   Harga\t: %d\n", buyingData.hargaGame);
	        printf("   stok\t\t: %d\n", buyingData.stokGame);
	        printf("   Total Harga\t: %d\n", buyingData.totalHarga);
			printf("   Status\t: %d\n", buyingData.statusPembelian);
	        i++;
		}

    }
    fclose(f_getAccount);
    int kodePembelian;
    printf("Kode data yang akan di Acc : ");
    scanf("%d",&kodePembelian);
	FILE *f_struktur;
	FILE *f_struktur_1;
    f_struktur=fopen("dataPembelian.dat","rb");
    f_struktur_1=fopen("dataPembelian_temp.dat","wb");
    //printf("Jumlah Stok : %d",buyingData.stokGame);
    while(fread(&buyingData,sizeof(buyingData),1,f_struktur)==1){
        if(kodePembelian == buyingData.kodePembelian){
        	strcpy(buyingData_list.username_penjual,buyingData.username_penjual);
    		strcpy(buyingData_list.username_pembeli,buyingData.username_pembeli);
    		strcpy(buyingData_list.namaGame,buyingData.namaGame);
			buyingData_list.hargaGame = buyingData.hargaGame;
			buyingData_list.stokGame = buyingData.stokGame;
			buyingData_list.totalHarga = buyingData.totalHarga;
			buyingData_list.kodePembelian = buyingData.kodePembelian;
        	buyingData_list.statusPembelian = buyingData.statusPembelian = 1;
        }
        fwrite(&buyingData,sizeof(buyingData),1,f_struktur_1);
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataPembelian.dat");
    rename("dataPembelian_temp.dat","dataPembelian.dat");
    if(buyingData_list.statusPembelian==1){
	    f_struktur=fopen("dataUser.dat","rb");
		f_struktur_1=fopen("dataUser_temp.dat","wb");
		//printf("Jumlah Stok : %d",buyingData.stokGame);
		while(fread(&dataUser,sizeof(dataUser),1,f_struktur)==1){
		    if(strcmp(buyingData_list.username_penjual,dataUser.username)==0 && strcmp(dataUser.role,"Penjual")==0){
		    	dataUser.saldo += buyingData_list.totalHarga;
		    }
		    if(strcmp(buyingData_list.username_pembeli,dataUser.username)==0 && strcmp(dataUser.role,"Pembeli")==0){
		    	dataUser.saldo -= buyingData_list.totalHarga;
			}
		    fwrite(&dataUser,sizeof(dataUser),1,f_struktur_1);
		}
		fclose(f_struktur);
		fclose(f_struktur_1);
		remove("dataUser.dat");
		rename("dataUser_temp.dat","dataUser.dat");
		//=====================================
		f_struktur=fopen("dataGame.dat","rb");
	    f_struktur_1=fopen("dataGame_temp.dat","wb");
	    //printf("Jumlah Stok : %d",buyingData.stokGame);
	    while(fread(&dataGame,sizeof(dataGame),1,f_struktur)==1){
	        if(strcmp(buyingData_list.namaGame,dataGame.namaGame)==0){
	        	dataGame.stokGame -= buyingData_list.stokGame;
	        }
	        fwrite(&dataGame,sizeof(dataGame),1,f_struktur_1);
	    }
	    fclose(f_struktur);
	    fclose(f_struktur_1);
	    remove("dataGame.dat");
	    rename("dataGame_temp.dat","dataGame.dat");
	    printf("\n\n====Acc Order Berhasil====\n\n");
	}else{
		printf("\n====Kode data tidak ditemukan====\n\n");
	}
}
//=============================== Pembeli
void pembeli(){
	int pilihan;
	printf("====Menu Pembeli====\n");
	printf("1. Sign UP\n2. Login\n3. Kembali\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");addPembeli();system("pause");system("cls");pembeli();break;
		case 2 	: system("cls");loginPembeli();break;
		case 3 	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");pembeli();
	}
}
void addPembeli(){
	printf("====Tambah Pembeli====\n");
    printf("Username\t: ");
    gets(dataUser.username);
    printf("Password\t: ");
    gets(dataUser.password);
    strcpy(dataUser.role, "Pembeli");
    dataUser.saldo = 0;
    FILE *f_addAccount;
    f_addAccount = fopen("dataUser.dat","ab");
    fwrite(&dataUser,sizeof(dataUser),1,f_addAccount);
    fclose(f_addAccount);
}
void loginPembeli(){
	char username[50],password[50];
	int percobaan_pembeli= 3;
	back:
	if(percobaan_pembeli == 0){
		system("cls");
		main();
	}
	printf("Kesempatan Login : %d\n",percobaan_pembeli);
    printf("====Login Pembeli====\n");
    printf("Username\t: ");
    gets(username);
    printf("Password\t: ");
    gets(password);
    //==================
    FILE *f_getAccount;
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
    	if(strcmp(username,dataUser.username)==0 && strcmp(password,dataUser.password)==0 && strcmp(dataUser.role,"Pembeli")==0){
    		status_login = 1;
    		strcpy(session_dataUser.username,dataUser.username);
    		strcpy(session_dataUser.password,dataUser.password);
    		strcpy(session_dataUser.role,dataUser.role);
			session_dataUser.saldo = dataUser.saldo;			
			break;
		}else{
			status_login = 0;
		}
    }
    fclose(f_getAccount);
    //printf("status_login : %d\n",status_login);
    if(status_login == 1){
    	printf("\n====Login Success====\n\n");
    	system("pause");
		system("cls");
    	berandaPembeli();
    	
	}else if(status_login == 0){
		printf("\n====Username or Password is invalid====");
		printf("\n\n");
		percobaan_pembeli--;
		system("pause");
		system("cls");
		goto back;
		
	}else{
		printf("\n====System Error====\n");
		main();
	}
}
void berandaPembeli(){
	int pilihan;
	FILE *f_getAccount;
	printf("====Data Pembeli====\n");
    f_getAccount = fopen("dataUser.dat","rb");
    while(fread(&dataUser,sizeof(dataUser),1,f_getAccount)==1){
    	if(strcmp(session_dataUser.username,dataUser.username)==0 && strcmp(session_dataUser.role,"Pembeli")==0){
			printf("Username \t: %s\n", dataUser.username);
	        printf("Saldo\t\t: %d\n", dataUser.saldo);
	        break;
        }
    }
    fclose(f_getAccount);
	printf("\n====Menu Aksi====\n");
	printf("1. Beli Game\n2. Isi saldo\n3. Refund Pembelian\n4. History Pembelian\n5. Logout\n");
	printf("Pilih Aksi : ");
	scanf("%d", &pilihan);getchar();
	switch(pilihan){
		case 1 	: system("cls");buyGame();system("pause");system("cls");berandaPembeli();break;
		case 2 	: system("cls");fillBalance();system("pause");system("cls");berandaPembeli();break;
		case 3  : system("cls");refundGame();system("pause");system("cls");berandaPembeli();break;
		case 4	: system("cls");buyingHistory();system("pause");system("cls");berandaPembeli();break;
		case 5	: system("cls");main();break;
		default : printf("\nTolong Pilih Angka dengan Benar!!\n\n");system("pause");system("cls");berandaPembeli();
	}
}
void buyGame(){
	FILE *f_getDataGame;
	printf("====Data Game====\n");
    int n=0,i,j;
    f_getDataGame = fopen("dataGame.dat","rb");
    while(fread(&dataGame,sizeof(dataGame),1,f_getDataGame)==1){
    	if(dataGame.stokGame <= 0){
    	continue;
		}
    	strcpy(dataGame_list[n].username,dataGame.username);
    	strcpy(dataGame_list[n].namaGame,dataGame.namaGame);
    	dataGame_list[n].hargaGame = dataGame.hargaGame;
    	dataGame_list[n].stokGame = dataGame.stokGame;
    	n++;
    }
    fclose(f_getDataGame);
	for (i = 0; i<n; i++){
	    for (j = 0; j < n; j++){
	        if (strcmp(dataGame_list[j-1].namaGame , dataGame_list[j].namaGame) >=0){
	            temp =dataGame_list[j-1]; 
	            dataGame_list[j - 1] = dataGame_list[j];
	            dataGame_list[j] = temp;
	        }
	    }
	}
	for (i = 0; i < n ; i++){
	    printf("%d. Nama Game\t: %s\n",i+1, dataGame_list[i].namaGame);
	    printf("   Username \t: %s\n",dataGame_list[i].username);
	    printf("   Harga\t: %d\n", dataGame_list[i].hargaGame);
	    printf("   stok\t\t: %d\n", dataGame_list[i].stokGame);
    }
    char target[50];
    int buyStok;
    printf("Nama Game yang ingin di beli : ");
    gets(target);
    f_getDataGame = fopen("dataGame.dat","rb");
    status_buyingData = 0;
    while(fread(&dataGame,sizeof(dataGame),1,f_getDataGame)==1){
    	if(strcmp(dataGame.namaGame,target)==0){
	    	strcpy(buyingData.username_penjual,dataGame.username);
	    	strcpy(buyingData.namaGame,dataGame.namaGame);
	    	buyingData.hargaGame = dataGame.hargaGame;
	    	buyingData.stokGame = dataGame.stokGame;
	    	status_buyingData = 1;
	    	break;
		}
    }
    fclose(f_getDataGame);
    if(status_buyingData==1){
    		printf("Jumlah Game yang ingin di beli : ");
		    scanf("%d",&buyStok);getchar();
		    if(buyStok>buyingData.stokGame){
		    	printf("====Warning====\n");
		    	printf("Jumlah stok Game kurang !!!\n");
		    	printf("Tolong beli jumlah game dengan stok yang sesuai !!!\n");
		    	system("pause");
		    	system("cls");
		    	buyGame();
			}
			buyingData.stokGame = buyStok;
			buyingData.totalHarga = buyingData.stokGame * buyingData.hargaGame;
    	if(dataUser.saldo >= buyingData.totalHarga){
			strcpy(buyingData.username_pembeli,session_dataUser.username);
			srand(time(0));
			buyingData.kodePembelian = rand();
			buyingData.statusPembelian = 0;
		    FILE *f_buyGame;
		    f_buyGame = fopen("dataPembelian.dat","ab");
		    fwrite(&buyingData,sizeof(buyingData),1,f_buyGame);
		    fclose(f_buyGame);
		    //========================================
		    /*
    		FILE *f_struktur;
			FILE *f_struktur_1;
		    f_struktur=fopen("dataGame.dat","rb");
		    f_struktur_1=fopen("dataGame_temp.dat","wb");
		    //printf("Jumlah Stok : %d",buyingData.stokGame);
		    while(fread(&dataGame,sizeof(dataGame),1,f_struktur)==1){
		        if(strcmp(buyingData.namaGame,dataGame.namaGame)==0){
		        	dataGame.stokGame -= buyingData.stokGame;
		        }
		        fwrite(&dataGame,sizeof(dataGame),1,f_struktur_1);
		    }
		    fclose(f_struktur);
		    fclose(f_struktur_1);
		    remove("dataGame.dat");
		    rename("dataGame_temp.dat","dataGame.dat");
		    */
		    if(status_buyingData==1){
				printf("\n  Proses Beli Game Berhasil\n\n");
			}else if(status_buyingData==0){
				printf("\n  Proses Beli Game Gagal\n\n");
			}else{
				printf("====Warning====\n");
				printf("\n====System Error====\n");
				exit(0);
			}
		}else if(dataUser.saldo <= buyingData.totalHarga){
			printf("====Warning====\n");
			printf("\n  Saldo tidak cukup \n\n");
		}
	}else if(status_buyingData==0){
		printf("====Warning====\n");
		printf("\n  Nama Game tidak ditemukan\n\n");
	}else{
		printf("====Warning====\n");
		printf("\n====System Error====\n");
		exit(0);
	}
}
void fillBalance(){
	FILE *f_struktur;
	FILE *f_struktur_1;
	int saldo_pembeli;
    printf("Jumlah Saldo : ");
    scanf("%d",&saldo_pembeli);
    f_struktur=fopen("dataUser.dat","rb");
    f_struktur_1=fopen("dataUser_temp.dat","wb");
    status_fillBalance = 0;
    while(fread(&dataUser,sizeof(dataUser),1,f_struktur)==1){
        if(strcmp(session_dataUser.username,dataUser.username)==0){
        	dataUser.saldo += saldo_pembeli;
            status_fillBalance = 1;
        }
        fwrite(&dataUser,sizeof(dataUser),1,f_struktur_1);
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataUser.dat");
    rename("dataUser_temp.dat","dataUser.dat");
    if(status_fillBalance == 1){
    	printf("\n====Saldo BERHASIL ditambah====\n");
	}else{
		printf("\n====Saldo GAGAL ditambah====\n");
	}
}
void refundGame(){
	printf("====History Pembelian====\n");
	FILE *f_getAccount;
    int i=1;
    f_getAccount = fopen("dataPembelian.dat","rb");
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
    	if(strcmp(session_dataUser.username,buyingData.username_pembeli)==0 && strcmp(session_dataUser.role,"Pembeli")==0 && buyingData.statusPembelian==1){
	    	printf("%d. ",i);
	        printf("Kode\t\t: %d\n", buyingData.kodePembelian);
	        printf("   Penjual \t: %s\n", buyingData.username_penjual);
	        printf("   Pembeli \t: %s\n", buyingData.username_pembeli);
	        printf("   Nama Game\t: %s\n", buyingData.namaGame);
	        printf("   Harga\t: %d\n", buyingData.hargaGame);
	        printf("   stok\t\t: %d\n", buyingData.stokGame);
	        printf("   Total Harga\t: %d\n", buyingData.totalHarga);
	        printf("   Status\t: Pembelian Berhasil\n",buyingData.statusPembelian);
	        i++;
	        printf("\n");
		}
    }
    fclose(f_getAccount);
    printf("\n");
    int kodePembelian;
    printf("Kode data yang akan di Refund : ");
    scanf("%d",&kodePembelian);
	FILE *f_struktur;
	FILE *f_struktur_1;
    f_struktur=fopen("dataPembelian.dat","rb");
    f_struktur_1=fopen("dataPembelian_temp.dat","wb");
    //printf("Jumlah Stok : %d",buyingData.stokGame);
    status_refund = 0;
    while(fread(&buyingData,sizeof(buyingData),1,f_struktur)==1){
        if(kodePembelian == buyingData.kodePembelian){
        	strcpy(buyingData_list.username_penjual,buyingData.username_penjual);
    		strcpy(buyingData_list.username_pembeli,buyingData.username_pembeli);
    		strcpy(buyingData_list.namaGame,buyingData.namaGame);
			buyingData_list.hargaGame = buyingData.hargaGame;
			buyingData_list.stokGame = buyingData.stokGame;
			buyingData_list.totalHarga = buyingData.totalHarga;
			buyingData_list.kodePembelian = buyingData.kodePembelian;
        	buyingData_list.statusPembelian = buyingData.statusPembelian = 2;
        	status_refund = 1;
        }
        fwrite(&buyingData,sizeof(buyingData),1,f_struktur_1);
    }
    fclose(f_struktur);
    fclose(f_struktur_1);
    remove("dataPembelian.dat");
    rename("dataPembelian_temp.dat","dataPembelian.dat");
    if(buyingData_list.statusPembelian==2){
    	if(status_refund == 1){
    		printf("\n====Proses Refund Game Berhasil====\n\n");
		}else if(status_refund = 0){
			printf("\n====Proses Refund Game Gagal====\n\n");
		}else{
			printf("\n====System Error !!!====\n\n");

		}
	}else{
		printf("\n====Refund Game Gagal====\n\n");
	}
}
void buyingHistory(){
	printf("====History Pembelian====\n");
	FILE *f_getAccount;
    int i=1;
    f_getAccount = fopen("dataPembelian.dat","rb");
    while(fread(&buyingData,sizeof(buyingData),1,f_getAccount)==1){
    	if(strcmp(session_dataUser.username,buyingData.username_pembeli)==0 && strcmp(session_dataUser.role,"Pembeli")==0){
	    	printf("%d. ",i);
	        printf("Kode\t\t: %d\n", buyingData.kodePembelian);
	        printf("   Penjual \t: %s\n", buyingData.username_penjual);
	        printf("   Pembeli \t: %s\n", buyingData.username_pembeli);
	        printf("   Nama Game\t: %s\n", buyingData.namaGame);
	        printf("   Harga\t: %d\n", buyingData.hargaGame);
	        printf("   stok\t\t: %d\n", buyingData.stokGame);
	        printf("   Total Harga\t: %d\n", buyingData.totalHarga);
	        if(buyingData.statusPembelian == 0){
	        	printf("   Status\t: Proses Pembelian \n",buyingData.statusPembelian);
			}else if(buyingData.statusPembelian == 1){
	        	printf("   Status\t: Pembelian Berhasil\n",buyingData.statusPembelian);
			}else if(buyingData.statusPembelian == 2){
	        	printf("   Status\t: Proses Refund \n",buyingData.statusPembelian);
			}else if(buyingData.statusPembelian == 3){
	        	printf("   Status\t: Refund Berhasil\n",buyingData.statusPembelian);
			}else{
				printf("   Status\t: Error \n",buyingData.statusPembelian);
			}
			printf("\n");
	        i++;
		}
    }
    fclose(f_getAccount);
    printf("\n\n");
}
//=================================