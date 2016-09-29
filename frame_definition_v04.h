//Estrutura para los paquetes recibidos, Nelson Gatica, 05-09-2016

typedef struct dataframe_received{
  int8_t start; //1B
  
  int16_t f_length;//2B
  
  int8_t  type;//1B
  
  int16_t address1;//2B 
  int16_t address2;//2B 
  int16_t address3;//2B 
  int16_t address4;//2B 

  int8_t rssi;//1B
  int8_t options;//1B
  int8_t data1;//1B
  int8_t data2;//1B
  int8_t data3;//1B
  int8_t Checksum;//1B  (TOTAL 18 Bytes)
};


typedef struct dataframe_send{
  int8_t start=0x7E; //1B
  
  int16_t f_length;//=0x0017;//2B
  
  int8_t  type=0x00;//1B

  int8_t  frame_id;//1B
     
  int16_t d_address1=0x0013;//2B 
  int16_t d_address2=0xA200;//2B 
  int16_t d_address3=0x40D9;//2B 
  int16_t d_address4=0xD527;//2B 

  int8_t options=0;//1B

  //Data  00 13 A2 00 40 F4 D3 26
  int16_t o_address1=0x0013;//2B 
  int16_t o_address2=0xA200;//2B 
  int16_t o_address3=0x40F4;//2B
  int16_t o_address4=0xD326;//2B 
  int8_t data1;//1B
  int8_t data2;//1B
  int8_t data3;//1B
  
  //int8_t data1;//1B
  //int8_t data2;//1B
  //int8_t data3;//1B
  
  int8_t Checksum;//1B  (TOTAL 18 Bytes)
};
/*union{
  int16_t b[2];
  uint32_t w;
}IMU_time;//antes solo int32_t
*/
