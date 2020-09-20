void kayit_bakim(){   
	int boskayit = defter.dosyabakim();
	if (boskayit == 0)
		cout << "Dosya bakim islemi gerceklestirilmistir. Bos kayit bulunamamistir."<< endl;
	else
		cout << "Dosya bakim islemi gerceklestirilmistir." << boskayit << " bos kayit dosyadan silinmistir."<<endl;
	getch();
};

int Dosya::dosyabakim(){    
	char *gecicidosyaadi = "geciciteldefteri.txt";
	FILE *geciciteldefteri;
	Tel_Kayit k;
	int sayac = 0;
	geciciteldefteri = fopen( gecicidosyaadi, "w+" );
	if(!geciciteldefteri){
		cerr << "Bakim icin gecici dosya acilamadi" << endl;
		exit(1);
	}
	fseek(teldefteri, 0, SEEK_SET);
	while(!feof(teldefteri)){
		fread( &k, sizeof (Tel_Kayit), 1, teldefteri);
		if(feof(teldefteri)) break;
		if((strcmp(k.ad,"")==0))
		sayac ++;
	else
	fwrite(&k, sizeof (Tel_Kayit), 1, geciciteldefteri);
	}	
	if(sayac > 0){
		fclose(teldefteri);
		fclose(geciciteldefteri);
		char komut[500]="cp ";
		strcat(komut,gecicidosyaadi);
		strcat(komut," ");
		strcat(komut,dosyaadi);
		system(komut);
		olustur();
	return sayac;
}