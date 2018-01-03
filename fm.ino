
byte data[50];
int offset = 0;
bool dataok = false;


int FrameLen; //19
unsigned int dist = 0;
float dist_pl;
int angle = 0;
float angle_pl;

void setup() 
{
  // put your setup code here, to run once:
  Serial2.begin(115200);
  Serial.begin(115200); //for debug
  //Serial2.setTimeout(200);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  while(Serial2.read() >= 0){}
  Serial2.readBytes(data, 50);
  while(1)
  {
      if(data[offset] == 0x59)
      {
          //Serial.println("found head");
          dist = 0;
          angle = 0;
          for(int i=0; i<50-offset-1; i++)
          {
            data[i] = data[offset+i];
          }
        
          FrameLen=data[1]; //19
          if(data[FrameLen-1]!='G')
          {
              //Serial.println("no G");
              break;
          }
          else
          {
            dist += data[10];
            dist += data[11] << 8;
          
            dist_pl = dist/100.;
          
            angle += data[12] & 0xff;
            angle += (data[13] & 0xff) << 8;
            
            angle_pl = angle/1000./M_PI*180;
            break;
          }
      }
      offset++;
      if (offset>=50)
      {
        //Serial.println("no 0x59");
        break;
      }
  }
  
  Serial.println(dist_pl);
  delay(200);

}
