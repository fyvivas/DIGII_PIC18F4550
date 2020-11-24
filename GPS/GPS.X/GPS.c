/*
    GPS Information extraction using PIC18F4550 
    http://www.electronicwings.com
*/

#include<pic18f4550.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
//#include "Configuration_Header_File.h"
#include "LCD_20x4_H_file.h"
#include "USART_Header_File.h"

void ADC_Init();
int ADC_Read(int);
unsigned long int get_gpstime();
float get_latitude(unsigned char);
float get_longitude(unsigned char);
float get_altitude(unsigned char);
void convert_time_to_UTC(unsigned long int);
float convert_to_degrees(float);

#define GGA_Buffer_Size 80
#define GGA_Pointers_Size 20

char GGA_Buffer[GGA_Buffer_Size];              /* to store GGA string */
char GGA_CODE[3];

unsigned char N_S, E_W;                        /* for getting direction polarity */
unsigned char GGA_Pointers[GGA_Pointers_Size]; /* to store instances of ',' */
char CommaCounter;
char Data_Buffer[15];
volatile unsigned int GGA_Index;
volatile unsigned char	IsItGGAString	= 0;
volatile unsigned char  IsEndGGA = 0;
volatile unsigned char  IsLastEndGGA = 0;

char Temperature[10];    
float celsius;
char stringBT [50]; 

void main(void) {
	unsigned long int Time;
	float Latitude,Longitude,Altitude;
	char GPS_Buffer[15];
    
    OSCCON = 0x72;      /* use internal osc. of 8MHz Freq. */
	LCD_Init();
    INTCONbits.GIE=1;   /* enable Global Interrupt */
    INTCONbits.PEIE=1;  /* enable Peripheral Interrupt */
    PIE1bits.RCIE=1;    /* enable Receive Interrupt */
	USART_Init(9600);
	ADC_Init();  
    
    //char testgps [100] = {"$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\0"};
    //int len = strlen(testgps);
    //int cmparray = strncmp("$GPGGA",testgps[0],6);
    
    // sendarrayBT  "time,lat,lon,temp"
    
    // sendarrayBT  "time,lat,lon,temp,ind,prese"
    
    // sendarrayBT  "time,lat,lon,temp,ind,v1,v2,v3"
    
    //aplicacion (COAP, MQTT, JSON, HTML) IoT
    //red
    //enlace
    //fisico
    
 
    
    // stringBT = "35,1245,2557,25"
    // stringBT = "35,1245,2557,25"
    // stringBT = "36,1245,2557,25"
    // stringBT = "35,1245,2557,25"
    // stringBT = "35,1245,2557,25"
    // stringBT = "42,1245,2557,25"
    // stringBT = "35,1245,2557,26"
    // stringBT = "35,1245,2557,25"
    // stringBT = "35,1245,2557,30"
    // stringBT = "35,1245,2557,25"
    // stringBT = "35,1245,2557,25"
    // stringBT = "35,1245,2557,50"
    // stringBT = "42,1245,2557,25"
    // stringBT = "35,1245,2557,25"

    
//    while(1){
//        
//        /* convert digital value to temperature */
//        celsius = (ADC_Read(0)*4.88);
//        celsius = (celsius/10.00);
//        /*convert integer value to ASCII string */
//        sprintf(Temperature,"%d%cC  ",(int)celsius,0xdf);
//        LCD_String_xy(1,0,"TEMP: ");
//        LCD_String(Temperature);
//        LCD_String("  "); 
//    
//    }
    
    while(1){
        
    /* convert digital value to temperature */
    celsius = (ADC_Read(0)*4.88);
    celsius = (celsius/10.00);
    /*convert integer value to ASCII string */
    sprintf(Temperature,"%d%cC  ",(int)celsius,0xdf);
    
    if(IsItGGAString == 0){
       //LCD_String_xy(1,0,"TEMP: ");
       //LCD_String(Temperature);
       //LCD_String("  ");  
    }
    else{
    
	memset(GPS_Buffer,0,15);
	LCD_String_xy(1,0,"UTC Time: ");
    Time = get_gpstime();            /* Extract Time */
	convert_time_to_UTC(Time);       /* convert time to UTC */
	LCD_String(Data_Buffer);
	LCD_String("  ");
	
    strcpy(stringBT, Data_Buffer); //timestamp
    strcat(stringBT, ",");
    
	LCD_String_xy(2,0,"Lat: ");
	Latitude = get_latitude(GGA_Pointers[0]); /* Extract Latitude */
	Latitude = convert_to_degrees(Latitude);  /* convert raw latitude in degree decimal*/
	sprintf(GPS_Buffer,"%.05f",Latitude);			/* convert float value to string */
	LCD_String(GPS_Buffer);            				/* display latitude in degree */
	strcat(stringBT, GPS_Buffer);
    strcat(stringBT, ",");
    
    memset(GPS_Buffer,0,15);
	LCD_String_xy(3,0,"Long: ");
	Longitude = get_longitude(GGA_Pointers[2]);/* Extract Latitude */
	Longitude = convert_to_degrees(Longitude);/* convert raw longitude in degree decimal*/
	sprintf(GPS_Buffer,"%.05f",Longitude);		/* convert float value to string */
	LCD_String(GPS_Buffer);            				/* display latitude in degree */
    strcat(stringBT, GPS_Buffer);
    strcat(stringBT, ",");
    
    memset(GPS_Buffer,0,15);
	LCD_String_xy(4,0,"Alt: ");
	Altitude = get_altitude(GGA_Pointers[7]); /* Extract Latitude */
	sprintf(GPS_Buffer,"%.2f",Altitude);			/* convert float value to string */
	LCD_String(GPS_Buffer);            				/* display latitude in degree */

    strcat(stringBT, Temperature);
    strcat(stringBT, "\r\n");
    USART_SendString(stringBT);  /* send LED ON status to terminal */
    }
    //modo de bajo consumo
	}
}

void ADC_Init()
{    
    TRISA = 0xFF;	/* Set as input port */
    ADCON1 = 0x0E;	/* Ref vtg is VDD and Configure pin as analog pin */
    ADCON2 = 0x92;	/* Right Justified, 4Tad and Fosc/32. */
    ADRESH=0;		/* Flush ADC output Register */
    ADRESL=0;   
}   

int ADC_Read(int channel)
{
    int digital;

    /* Channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000) & ADC is disabled */
    ADCON0 =(ADCON0 & 0b11000011)|((channel<<2) & 0b00111100);  
    
    ADCON0 |= ((1<<ADON)|(1<<GO));	/*Enable ADC and start conversion*/

    /* Wait for End of conversion i.e. Go/done'=0 conversion completed */
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);	/*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}


unsigned long int get_gpstime(){
	unsigned char index;
	unsigned char Time_Buffer[15];
	unsigned long int _Time;
	
	/* parse Time in GGA string stored in buffer */
	for(index = 0;GGA_Buffer[index]!=','; index++){		
		Time_Buffer[index] = GGA_Buffer[index];
	}
	_Time= atol(Time_Buffer);        /* convert string of Time to integer */
	return _Time;                    /* return integer raw value of Time */        
}

//float get_latitude(unsigned char);

float get_latitude(unsigned char lat_pointer){
	unsigned char lat_index = lat_pointer+1;	/* index pointing to the latitude */
	unsigned char index = 0;
	char Lat_Buffer[15];
	float _latitude;

	/* parse Latitude in GGA string stored in buffer */
	for(;GGA_Buffer[lat_index]!=',';lat_index++){
		Lat_Buffer[index]= GGA_Buffer[lat_index];
		index++;
	}
    lat_index++;
    N_S = GGA_Buffer[lat_index];
	_latitude = atof(Lat_Buffer);     /* convert string of latitude to float */
	return _latitude;                 /* return float raw value of Latitude */
}

float get_longitude(unsigned char long_pointer){
	unsigned char long_index;
	unsigned char index = long_pointer+1;		/* index pointing to the longitude */
	char Long_Buffer[15];
	float _longitude;
	long_index=0;
	
	/* parse Longitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Long_Buffer[long_index]= GGA_Buffer[index];
		long_index++;
	}
    long_index++;
    E_W = GGA_Buffer[long_index];
	_longitude = atof(Long_Buffer);    /* convert string of longitude to float */
	return _longitude;                 /* return float raw value of Longitude */
}

float get_altitude(unsigned char alt_pointer){
	unsigned char alt_index;
	unsigned char index = alt_pointer+1;	/* index pointing to the altitude */
	char Alt_Buffer[12];
	float _Altitude;
	alt_index=0;
	
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Alt_Buffer[alt_index]= GGA_Buffer[index];
		alt_index++;
	}
		_Altitude = atof(Alt_Buffer);   /* convert string of altitude to float */ 
	return _Altitude;                 /* return float raw value of Altitude */
}

void convert_time_to_UTC(unsigned long int UTC_Time)
{
	unsigned int hour, min, sec;
		
	hour = (UTC_Time / 10000);                  /* extract hour from integer */
	min = (UTC_Time % 10000) / 100;             /* extract minute from integer */
	sec = (UTC_Time % 10000) % 100;             /* extract second from integer*/

	sprintf(Data_Buffer, "%d:%d:%d", hour,min,sec); /* store UTC time in buffer */
	
}

float convert_to_degrees(float NMEA_lat_long){
	
	
	float minutes, dec_deg, decimal;
	
	int degrees;
	
	float position;

    degrees = (int)(NMEA_lat_long/100.00);
    minutes = NMEA_lat_long - degrees*100.00;
    dec_deg = minutes / 60.00;
    decimal = degrees + dec_deg;
    if (N_S == 'S' || E_W == 'W') { // return negative
        decimal *= -1;
    }	
	/* convert raw latitude/longitude into degree format */
	return decimal;
}


void __interrupt () Serial_ISR (void) {

//void interrupt Serial_ISR()   
//{
	 
	if(RCIF){
		GIE  = 0;							/* Disable global interrupt */
		unsigned char received_char = RCREG;
        if(RCSTAbits.OERR){                 /* check if any overrun occur due to continuous reception */           
            CREN = 0;
            NOP();
            CREN=1;
        }
        
		if(received_char =='$'){                                                    /* check for '$' */
			GGA_Index = 0;
			IsItGGAString = 0;
            IsLastEndGGA = 0;
			CommaCounter = 0;
            IsEndGGA = 0;
		}
		else if(IsItGGAString == 1){                                             /* if true save GGA info. into buffer */
			if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;    /* store instances of ',' in buffer */
			GGA_Buffer[GGA_Index++] = received_char;
            if(received_char == '\n'){
                if (IsLastEndGGA == '\r'){
                    IsEndGGA = 1;
                }
            }
            else{
                IsLastEndGGA = received_char;
            }
        }
		else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){ /* check for GGA string */
			IsItGGAString = 1;
			GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;	
		}
		else{
			GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char; 
		}	
	}
}