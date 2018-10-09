//Od Kuby
#include<bits/stdc++.h>
#include<inttypes.h>

using namespace std;
void secret(uint8_t *to, uint8_t *from, size_t count) {
    size_t n = (count + 7) / 8;
    switch (count % 8) {
    case 0: do { *to++ = *from++;
    case 7: *to++ = *from++;
    case 6: *to++ = *from++;
    case 5: *to++ = *from++;
    case 4: *to++ = *from++;
    case 3: *to++ = *from++;
    case 2: *to++ = *from++;
    case 1: *to++ = *from++;
    } while (--n > 0);
    }
}


void secret_modified(uint8_t* to, uint8_t* from, size_t count) {
	size_t n = (count + 7) / 8; // sufit count/8
	int reszta = count % 8;
	if (reszta == 0) goto label_0;
	else if (reszta == 1) goto label_1;
	else if (reszta == 2) goto label_2;
	else if (reszta == 3) goto label_3;
	else if (reszta == 4) goto label_4;
	else if (reszta == 5) goto label_5;
	else if (reszta == 6) goto label_6;
	else if (reszta == 7) goto label_7;

label_0: *to++ = *from++;
label_7: *to++ = *from++;
label_6: *to++ = *from++;
label_5: *to++ = *from++;
label_4: *to++ = *from++;
label_3: *to++ = *from++;
label_2: *to++ = *from++;
label_1: *to++ = *from++;
	if (n == 0) return;
	n--;
	goto label_0;
}


int main()
{
	
	uint8_t tablica[12] = { 12, 32, 65, 89, 1, 2, 3, 4, 5, 6, 7, 8 };
	uint8_t tablica2[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };

	secret_modified(tablica2, tablica, 4);
		

	int test[5] = { 1, 2, 3, 4, 5 };
	int i = 2;
	test[++i] = 20;
        cout<<i<<"\n";
	for (int i = 0; i < 5; i++)
	{
		cout << test[i] << endl;
	}

	return 0;
}