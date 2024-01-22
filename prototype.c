//Ներառում ենք անհրաժեշտ գրադարանները
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// գրադարան անիմացիայի համար
#include <ncurses.h>
// անհրաժեշտ է դանդաղ անիմացիայի համար
#include <unistd.h>

//Սրանք ֆունկցիաների հայտարարություններն են
// Դրանց մասին կխոսենք հետագայում
void swap(int*, int, int, int, int);
void ArrSort(int, int*, int*, int*, int*, int*, int, int);
int* createRandArr(int);
void counter(int*, int*, int*, int*, int);
void goLeft(int, int, int*, int, int, int); 

int main(){

    // Մինչև ծրագրի բուն անշխատանքին անցնելը
    // օգտատերը ներմուծում է զանվածի երկարության չափը
    int len;
    printf("Input the length of array: ");
    scanf("%d", &len);

    // Հետևյալ ֆունկցիաների կանչերը անհրաժեշտ են
    // ծրագրի պարշաճ աշխատանքի համար

    // ակտիվացվում է պատուհան անիմացիայի համար
	initscr();
    // չեն երևում ստեղնի ներմուծումները
	noecho();
    // անսարքումների դեպքում համակարգի կողմից դրանց շտկում
	raw();
    // ստեղնաշարի ակտիվացում մոնիտորի անբողջ երկայնքով
	keypad(stdscr, TRUE);
    // անջատվում է կուրսորը
    curs_set(0);

    // գուների տվյալների ներմուծում
	if (has_colors()) {
        // գույների օգտվելու թույլտվության ակտիվացում
        start_color();

        // թիվ 1: կարմիր
        init_pair(1, COLOR_RED, COLOR_BLACK);
        // թիվ 2: կանաչ
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        
    }

    // այս հրամանը հնարավորություն է տալիս ստանալու
    // պատահական արժեքներ
	srand(time(0));

    // հայտարարենք փոփոխականներ
	int countNeg = 0, countPos = 0, countZero = 0;
	int end = 0;
	int x, y;
	int num = 0;

    // ստանում ենք մոնիտորի չափսերը 
	getmaxyx(stdscr, y, x);

    // ստեղծում ենք պատահական արժեքներով 
    // միաչափ զանգված
	int* arr = createRandArr(len); 

    //ստանում ենք բացասական , դրական թվերի և
    // զրոների քանակը
	counter(arr, &countZero, &countPos, &countNeg, len);

    // կատարում ենք սորտավորման գործողությունը այնքան , 
    // մինչև օգտատերը չսեղմի ESC ստեղնը
    do{
        // տեղաշարժում կուրսորը համապատասխան շեղմամբ
        move(y / 2 - 10, x / 2 - 17);
		printw("Press ESC to exit the programm");

        // Այս ֆունկցիան սորտավորում է զանգվածը և
        // ցույց տալիս էկրանին
		ArrSort(len, arr, &countZero, &countPos, &countNeg, &num, x, y);
        getch();
    }
	while ((end = getch()) != 27);
    
    // ազատվում է "Կույտից" «Heap» հիշողությունը
	free(arr);

    //ծրագրի ավարտ
	endwin();

	return 0;
}

// հետևյալ ֆունկցիան ստացված զանգվածի արժեքը տպում է վերև ըստ ներմուծված
// շեղման
void printToUp(int* arr, int CEI, int x, int y, int offsetUp, int len){
	usleep(100000);
    clear();
    move(y / 2 - 10, x / 2 - 17);
    printw("Press ESC to exit the programm");
    for(int i = 0; i < len; ++i){
		move(y / 2, x / 2 - len * 2 + i * 4);
        if(i == CEI){
            move(y / 2 - offsetUp, x / 2 - len * 2 + i * 4);
            attron(COLOR_PAIR(1));
            printw("%d", arr[i]);
            attroff(COLOR_PAIR(1));
            refresh();
        }
        else{
            printw("%d", arr[i]);
            refresh();
        }
    }
}

// հետևյալ ֆունկցիան ստացված զանգվածի արժեքը տպում է ձախ և վերև ըստ ներմուծված
// շեղումների
void printToLeft(int* arr, int CEI, int x, int y, int offsetUp, int offsetLeft, int len){
	usleep(100000);
    clear();
    move(y / 2 - 10, x / 2 - 17);
    printw("Press ESC to exit the programm");
    for(int i = 0; i < len; ++i){
		move(y / 2, x / 2 - len * 2 + i * 4);
        if(i == CEI){
            move(y / 2 - offsetUp, x / 2 - len * 2 + i * 4 - offsetLeft);
            attron(COLOR_PAIR(1));
            printw("%d", arr[i]);
            attroff(COLOR_PAIR(1));
            refresh();
        }
        else{
            printw("%d", arr[i]);
            refresh();
        }
    }
}

// հետևյալ ֆունկցիան ստացված զանգվածի արժեքը տպում է ձախ և ներքև ըստ ներմուծված
// շեղումների
void printToDown(int* arr, int CEI, int x, int y, int offsetDown, int offsetLeft, int len){
	usleep(100000);
    clear();
    move(y / 2 - 10, x / 2 - 17);
    printw("Press ESC to exit the programm");
    for(int i = 0; i < len; ++i){
		move(y / 2, x / 2 - len * 2 + i * 4);
        if(i == CEI){
            move(y / 2 - offsetDown, x / 2 - len * 2 + i * 4 - offsetLeft);
            attron(COLOR_PAIR(1));
            printw("%d", arr[i]);
            attroff(COLOR_PAIR(1));
            refresh();
        }
        else{
            printw("%d", arr[i]);
            refresh();
        }
    }
}

// հետևյալ ֆունկցիան ստացված զանգվածի արժեքը տպում է աջ ըստ ներմուծված շեղումի
void printToRight(int* arr, int CEI, int x, int y, int offsetUp, int offsetLeft, int offsetRight, int len){
	usleep(100000);
    clear();
    move(y / 2 - 10, x / 2 - 17);
    printw("Press ESC to exit the programm");
    for(int i = 0; i < len; ++i){
		move(y / 2, x / 2 - len * 2 + i * 4);
        if(i == CEI - 1){
            move(y / 2, x / 2 - len * 2 + i * 4 + offsetRight);
            attron(COLOR_PAIR(2));
			printw("%d", arr[i]);
			attroff(COLOR_PAIR(2));
            refresh();
        }
        else if(i == CEI){
            move(y / 2 - offsetUp, x / 2 - len * 2 + i * 4 - offsetLeft);
            attron(COLOR_PAIR(1));
            printw("%d", arr[i]);
            attroff(COLOR_PAIR(1));
            refresh();
        }
        else{
            printw("%d", arr[i]);
            refresh();
        }
    }
}

// Այս ֆունկցիան կազմակերպում է երկու կից էլեմենտների
// տեղափոխությունը օգտագործելով նախորդ ֆունկցիաները
// անիմացիայի էֆֆեկտ ստանալու նպատակով
void swap(int* arr, int CEI, int x, int y, int len){ // CEI -> current elements index
	for(int i = 0; i < len; ++i){
		move(y / 2, x / 2 - len * 2 + i * 4);
		printw("%d", arr[i]);
		refresh();
	}
	printToUp(arr, CEI, x, y, 1, len);
    printToUp(arr, CEI, x, y, 2, len);
    printToLeft(arr, CEI, x, y, 2, 2, len);
    printToLeft(arr, CEI, x, y, 2, 4, len);
    printToDown(arr, CEI, x, y, 1, 4, len);
    printToRight(arr, CEI, x, y, 1, 4, 2, len);
    printToRight(arr, CEI, x, y, 1, 4, 4, len);
    printToRight(arr, CEI, x, y, 0, 4, 4, len);
    int tmp = arr[CEI];
    arr[CEI] = arr[CEI - 1];
    arr[CEI - 1] = tmp;
	usleep(100000);
	int end = getch();
	if( end == 27 ){
		endwin();
		exit(0);
	}
}

// Ֆունկցիա , որը ընտրված էլէմենտը ՝ օգտագործելով նախորդ ֆունցիաները
// հասցնում է իրեն նախատեսված տեղը
void goLeft(int from, int to, int* arr, int x, int y, int len){
	for(int i = from; i > to; i--){
		swap(arr, i, x, y, len);
	}
}

// հետևալ մեծ ֆունկցիան խմբավորում է բոլոր գրված ֆունկցիաները 
// որի արդյունքում կազմակերպվում է զանգվածի ամբողջական սորտավորումը
// և էկրանին անիմացիայի ցույց տալը
void ArrSort(int len, int* arr, int* countZero, int* countPos, int* countNeg, int* num, int x, int y){
	for(int i = 0; i < len; ++i){
		if(*countZero != 0 && *countPos != 0 && *countNeg != 0){
			if((i % 3) == 0){
				if(arr[i] >= 0){
					for(int j = i + 1; j < len; ++j){
						if(arr[j] < 0){
							goLeft(j, i, arr, x, y, len);
							break;
						}
					}
				}
				--(*countNeg);
			}
			else if((i % 3) == 1){
				if(arr[i] != 0){
					for(int j = i + 1; j < len; ++j){
						if(arr[j] == 0){
							goLeft(j, i, arr, x, y, len);
							break;
						}
					}
				}
				--(*countZero);
			}
			else if((i % 3) == 2){
				if(arr[i] <= 0){
					for(int j = i + 1; j < len; ++j){
						if(arr[j] > 0){
							goLeft(j, i, arr, x, y, len);
							break;
						}
					}
				}
				--(*countPos);
			}
			*num = i;
		}
		else{
			int parity = (*num % 2 == 0) ? 1 : 0;
			if(*countZero == 0){
				for(int i = *num + 1; i < len; ++i){
					if(i % 2 == parity){
						if(arr[i] < 0){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] > 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
					else if(i % 2 == parity - 1){
						if(arr[i] > 0){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] < 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
				}
			}
			else if(*countNeg == 0){
				for(int i = *num + 1; i < len; ++i){
					if(i % 2 == parity){
						if(arr[i] != 0){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] == 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
					else if(i % 2 == parity - 1){
						if(arr[i] < 0){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] > 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
				}
			}
			else if(*countPos == 0){
				for(int i = *num + 1; i < len; ++i){
					if(i % 2 == parity){
						if(arr[i] >= 0){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] < 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
					else if(i % 2 == 1){
						if(arr[i] != parity - 1){
							for(int j = i + 1; j < len; ++j){
								if(arr[j] == 0){
									goLeft(j, i, arr, x, y, len);
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

// ֆունցիա, որը վերադարձնում է ներմուծված երկարության
// վրա "Կույտում" ցույց տվող ցուցիչ
int* createRandArr(int len){
	int* arr = (int*) malloc(len * sizeof(int));

	for(int i = 0; i < len; ++i){
		if(i % 6 == 0)
			arr[i] = 0;
		else
			arr[i] = rand() % 21 - 10;
	}

	return arr;
}

// ֆունկցիա , որը հաշվում է բացասական , դրական թվերի , և զրոների քանակակը
void counter(int* arr, int* countZero, int* countPos, int* countNeg, int len){
	for(int i = 0; i < len; ++i){
		if(arr[i] == 0){
			(*countZero)++;
			continue;
		}
		if(arr[i] > 0){
			(*countPos)++;
			continue;
		}
		if(arr[i] < 0){
			(*countNeg)++;
			continue;
		}
	}
}