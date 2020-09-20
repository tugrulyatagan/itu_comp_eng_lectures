#include <iostream>             // cin,cout,cerr,endl
#include <stdio.h>              // fopen,fclose,fprintf,fscanf,feof
#include <stdlib.h>             // exit,EXIT_SUCCESS,EXIT_FAILURE
#include <math.h>               // fabs,sqrt

using namespace std;

#define MAXSTUDENTS 100

int main(int argc, char *argv[])
{
    int score[MAXSTUDENTS];
    int no_students = 0;
    float mean, variance, std_dev, abs_dev;
    float total = 0.0, sqr_total = 0.0, abs_total = 0.0;
    int i = 0;
    FILE *infile, *outfile;

    if (argc != 3) {
        cout << "Kullanim: " << argv[0]
             << "  giris_dosyasi  cikis_dosyasi" << endl;
        return EXIT_FAILURE;
    }

    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        cerr << "Giris dosyasi acilamadi." << endl;
        exit(EXIT_FAILURE);
    }

    no_students = 0;
    while (true) {
        fscanf(infile, "%d", &score[no_students]);
        if (feof(infile))
            break;
        total = total + score[no_students];
        no_students++;
    }
    fclose(infile);

    mean = total / no_students;
    for (i = 0; i < no_students; i++) {
        sqr_total = sqr_total + (score[i] - mean) * (score[i] - mean);
        abs_total = abs_total + fabs(score[i] - mean);
    }
    variance = sqr_total / (no_students - 1);
    std_dev = sqrt(variance);
    abs_dev = abs_total / no_students;

    outfile = fopen(argv[2], "w");
    if (outfile == NULL) {
        cerr << "Cikis dosyasi acilamadi." << endl;
        exit(EXIT_FAILURE);
    }

    fprintf(outfile, "Ogrenci sayisi: %d\n", no_students);
    fprintf(outfile, "Ortalama: %.2f\n", mean);
    fprintf(outfile, "Varyans: %.2f\n", variance);
    fprintf(outfile, "Standart sapma: %.2f\n", std_dev);
    fprintf(outfile, "Mutlak sapma: %.2f\n", abs_dev);

    fclose(outfile);

    return EXIT_SUCCESS;
}
