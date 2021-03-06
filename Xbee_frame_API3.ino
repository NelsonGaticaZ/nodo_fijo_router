//Este programa es para poder recibir un frame desde un nodo móvil y enviar un frame API al Coordinador ///
//Última modificación hecha por Nicolas Roa el jueves 22 de septiembre del 2016                         ///
//Última modificación hecha por Nelson Gatica el jueves 29 de Septiembre del 2016, 18:01 horas          ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//Serial virtual
#include <SoftwareSerial.h>

//Construye la estructura del frame de datos a enviar
#include "frame_definition_v04.h" 

//Definición de variables
unsigned char   buf_received[24];     //
unsigned char   buf_send[35];       //
int count=0;              
byte pin_test=5;
int altura_nf=300;  //En centímetros          
  
//Definición de objetos
dataframe_received F_received;
//dataframe_send     F_send;
SoftwareSerial mySerial(7, 8);      // RX, TX

void setup() {
  Serial.begin(57600);        //Velocidad de comunicación Serial
  pinMode(pin_test,OUTPUT);
    mySerial.begin(57600);        //Velocidad de comunicación Serial Virtual
}

void loop(){ 
 if (Serial.available()){
  //digitalWrite(pin_test,1);
  delay(10);//CUIDADO CON ESTE RETARDO; ES NECESARIO PARA TERMINAR DE LLENAR EL BUFFER
        while(Serial.available()){               // reading data into char array
            buf_received[count++]=Serial.read();      // writing data into array
            if(count == sizeof(buf_received))break;
        }
        received_frame();
        make_frame_b();
    //make_frame_a();
        clearBufferArray();                         // call clearBufferArray function to clear the stored data from the array  
 }
}

void clearBufferArray(){// function to clear buffer array
    for (int i=0; i<count;i++){ 
     buf_received[i]=NULL;
     }
     count = 0;
}

void received_frame(){  
//dataframe_received *p_F_received = &F_received;
F_received.start    = buf_received[0];
F_received.f_length = buf_received[1]<<8 | buf_received[2];
F_received.type     = buf_received[3];

F_received.address1 = buf_received[5]<<8 | buf_received[4];
F_received.address2 = buf_received[7]<<8 | buf_received[6];
F_received.address3 = buf_received[9]<<8 | buf_received[8];
F_received.address4 = buf_received[11]<<8 | buf_received[10];

F_received.rssi     = buf_received[12];
F_received.options  = buf_received[13];

F_received.data1    = buf_received[14];
F_received.data2    = buf_received[15];
F_received.data3    = buf_received[16];
F_received.data4    = buf_received[17];
F_received.data5    = buf_received[18];
F_received.data6    = buf_received[19];
F_received.data7    = buf_received[20];
F_received.data8    = buf_received[21];
F_received.data9    = buf_received[22];
F_received.Checksum = buf_received[23];

  //for(int i=0;i<sizeof(buf_received);i++)
    //mySerial.write(buf_received[i]);
}


void make_frame_a(){
buf_send[0] = 0x7E;             //Start

buf_send[1] = 0x00;             //length    //buf_send[2] = sizeof(buf_send)-4;
buf_send[2] = 0x17;             //length 
buf_send[3] = 00;               //type
buf_send[4] = 0x00;             //frame_id

buf_send[5] = 0x00;             //d_address direccion destino (coordinador)
buf_send[6] = 0x13;             //d_address
buf_send[7] = 0xA2;             //d_address
buf_send[8] = 0x00;             //d_address
buf_send[9]  = 0x40;            //d_address
buf_send[10] = 0xD9;            //d_address
buf_send[11] = 0xD5;            //d_address
buf_send[12] = 0x27;            //d_address

buf_send[13] = 0x00;            //options 

buf_send[14] = buf_received[4];       //o_address direccion origen (n movil)
buf_send[15] = buf_received[5];       //o_address
buf_send[16] = buf_received[6];       //o_address
buf_send[17] = buf_received[7];       //o_address
buf_send[18] = buf_received[8];       //o_address
buf_send[19] = buf_received[9];       //o_address
buf_send[20] = buf_received[10];      //o_address
buf_send[21] = buf_received[11];      //o_address

buf_send[22] = buf_received[12];      //rssi
buf_send[23] = buf_received[14];      //data1
buf_send[24] = buf_received[15];      //data2
buf_send[25] = buf_received[16];      //data3


unsigned char check_sum=0xFF;
  for (int i=3; i<=(sizeof(buf_send)-2); i++){
    check_sum =check_sum - buf_send[i];  
  }
    buf_send[26]=check_sum;
    delay(250);
  
    Serial.write(buf_send,sizeof(buf_send));  //envio al coordinador
    mySerial.write(buf_send,sizeof(buf_send)); 
}

void make_frame_b(){
buf_send[0] = 0x7E;             //start

buf_send[1] = 0x00;             //length    //buf_send[2] = sizeof(buf_send)-4;
buf_send[2] = 0x1F;             //length 
buf_send[3] = 00;               //type
buf_send[4] = 0x00;             //frame_id

buf_send[5] = 0x00;             //d_address direccion destino (coordinador)
buf_send[6] = 0x13;             //d_address
buf_send[7] = 0xA2;             //d_address
buf_send[8] = 0x00;             //d_address
buf_send[9]  = 0x40;            //d_address
buf_send[10] = 0xD9;            //d_address
buf_send[11] = 0xD5;            //d_address
buf_send[12] = 0x27;            //d_address

buf_send[13] = 0x00;            //options 

buf_send[14] = buf_received[4];       //o_address direccion origen (n movil)
buf_send[15] = buf_received[5];       //o_address
buf_send[16] = buf_received[6];       //o_address
buf_send[17] = buf_received[7];       //o_address
buf_send[18] = buf_received[8];       //o_address
buf_send[19] = buf_received[9];       //o_address
buf_send[20] = buf_received[10];      //o_address
buf_send[21] = buf_received[11];      //o_address

buf_send[22] = buf_received[12];      //rssi
buf_send[23] = buf_received[14];      //data1 ep1
buf_send[24] = buf_received[15];      //data2 ep2
buf_send[25] = buf_received[16];      //data3 ep3
buf_send[26] = buf_received[17];      //data1 ep4
buf_send[27] = buf_received[18];      //data2 ndis
buf_send[28] = buf_received[19];      //data3 nmsg
buf_send[29] = buf_received[20];      //data1 pot
buf_send[30] = buf_received[21];      //data2 ver
buf_send[31] = buf_received[22];      //data3 alturanm
buf_send[32] = 0x01;            //altura nf
buf_send[33] = 0x2c;            //altura nf

unsigned char check_sum=0xFF;
  for (int i=3; i<=(sizeof(buf_send)-2); i++){
    check_sum =check_sum - buf_send[i];  
  }
    buf_send[34]=check_sum;
    delay(250);
  
    Serial.write(buf_send,sizeof(buf_send));  //envio al coordinador
    mySerial.write(buf_send,sizeof(buf_send)); 
}
