int R = D0 ;
int G = D3 ;
int B = D4 ;

void setup()
{
 pinMode(R,OUTPUT);
 pinMode(G,OUTPUT);
 pinMode(B,OUTPUT);
}

void loop()
{
analogWrite(R,255);
analogWrite(G,0);
analogWrite(B,0);
delay(2000);

analogWrite(R,0);
analogWrite(G,255);
analogWrite(B,0);
delay(2000);

analogWrite(R,0);
analogWrite(G,0);
analogWrite(B,255);
delay(2000);
}
