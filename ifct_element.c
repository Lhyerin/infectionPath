//
//  ifs_element.c
//  InfestPath
//
//  Created by Juyeop Kim on 2020/10/20.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ifct_element.h"

typedef enum place {
    Seoul,          //0
    Jeju,           //1
    Tokyo,          //2
    LosAngeles,     //3
    NewYork,        //4
    Texas,          //5
    Toronto,        //6
    Paris,          //7
    Nice,           //8
    Rome,           //9
    Milan,          //10
    London,         //11
    Manchester,     //12
    Basel,          //13
    Luzern,         //14
    Munich,         //15
    Frankfurt,      //16
    Berlin,         //17
    Barcelona,      //18
    Madrid,         //19
    Amsterdam,      //20
    Stockholm,      //21
    Oslo,           //22
    Hanoi,          //23
    Bangkok,        //24
    KualaLumpur,    //25
    Singapore,      //26
    Sydney,         //27
    SaoPaulo,       //28
    Cairo,          //29
    Beijing,        //30
    Nairobi,        //31
    Cancun,         //32
    BuenosAires,    //33
    Reykjavik,      //34
    Glasgow,        //35
    Warsow,         //36
    Istanbul,       //37
    Dubai,          //38
    CapeTown        //39
} place_t;

char countryName[N_PLACE+1][MAX_PLACENAME] =
{   "Seoul",
    "Jeju",
    "Tokyo",
    "LosAngeles",
    "NewYork",
    "Texas",
    "Toronto",
    "Paris",
    "Nice",
    "Rome",
    "Milan",
    "London",
    "Manchester",
    "Basel",
    "Luzern",
    "Munich",
    "Frankfurt",
    "Berlin",
    "Barcelona",
    "Madrid",
    "Amsterdam",
    "Stockholm",
    "Oslo",
    "Hanoi",
    "Bangkok",
    "KualaLumpur",
    "Singapore",
    "Sydney",
    "SaoPaulo",
    "Cairo",
    "Beijing",
    "Nairobi",
    "Cancun",
    "BuenosAires",
    "Reykjavik",
    "Glasgow",
    "Warsow",
    "Istanbul",
    "Dubai",
    "CapeTown",
    "Unrecognized"
};


//return country name pointer from country number
char* ifctele_getPlaceName(int placeIndex) //placeindex는 장소번호로, 장소번호를 받아온다.  
{
	return countryName[placeIndex]; // 
}

typedef struct ifs_ele {
	int index; //번호 -> 정수 
	int age; //나이  -> 정수 
	unsigned int detected_time; //감염 시점 -> 정수  
    place_t history_place[N_HISTORY]; //감염 직전 이동경로(개수만큼 있을 거임) -> enum을 활용.(enum place_t) 정수 배열을 선언 (N_HISTORY) 
} ifs_ele_t; //애칭을 설정해주는 거임. (부르기 편하게) 

void* ifctele_genElement(int index, int age, unsigned int detected_time, int history_place[N_HISTORY]) //main 함수에서 환자의 정보를 불려왓을 떄 구조체로 만들어서 포인터로 변환해주는)
{
	ifs_ele_t *ptr;
	
	ptr = (ifs_ele_t *)malloc(sizeof(ifs_ele_t));
	ptr->index =index;  //번호 
	ptr-> age=age;     //나이  
	ptr-> detected_time = detected_time;   //감염시점 
  	for (int i=0;i<N_HISTORY;i++)      // 반복문을 돌려서 i번째 장소를 나타낸다. 
		ptr-> history_place[i]= (place_t)history_place[i];
	
	return ptr;	
}

int ifctele_getAge(void* obj) //포인터 대상을 받아옵니다. 
{
	ifs_ele_t *stPtr =(ifs_ele_t*)obj;
	return stPtr -> age; //age를 반환해준다. 
}

void ifctele_printElement(void* obj) //포인터 대상을 받아옵니다. 
{
	ifs_ele_t *ptr=(ifs_ele_t*)obj; 
	printf("patient age : %i\n", ptr->age); //환자의 나이를 출력 
	printf("detected time : %i\n", ptr->detected_time); //감염된 시점을 출력 
	for(int i=0;i<5;i++)
	{
		printf("place No.%i :%s(%i)\n",i+1,ifctele_getPlaceName(ptr-> history_place[i]),ptr->detected_time-4+i);  // 장소와 함께 시점을 출력 
	}
}

int ifctele_getHistPlaceIndex(void* obj, int index) // 구조체로부터 장소 번호를 추출해주는 함수이다.  (문자열을 받으면 번호를 준다.)  
{
	ifs_ele_t *ptr=(ifs_ele_t*)obj;
	return ptr->history_place[index]; //index번째의 장소 번호를 ptr. 
	
}

unsigned int ifctele_getinfestedTime(void* obj) // (void*obj)=포인터 대상을 받아옵니다. 
{
	ifs_ele_t *stPtr =(ifs_ele_t*)obj;
	return stPtr -> detected_time; //감염된 시점을 ptr. 
}		    
