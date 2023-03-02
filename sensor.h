void updateSensors()
    {
    humidity =   dht.readHumidity();        
    tempC =      dht.readTemperature();      // Read temperature as Celsius 
    tempF =      dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)

    //if any value is isnan (not a number) then there is an error
    if (isnan(humidity) || isnan(tempC) || isnan(tempF))        
    { 
       Serial.println("Erreur de lecture DHT22."); 
    }
   else
    {   
      moyC += tempC;   
      moyH += humidity;;
      Serial.println(moyH);
      moy++;    
      if (moy > 59){
        for (int i = 0; i < 20; i++)
        {
          temp[i] = temp[i +1];
          hum[i] = hum[i +1];
        }        
        moyC = moyC/60;   
        moyH = moyH/60;
        temp[19] = moyC;
        hum[19] = moyH;
        moy = 0;
        moyC = 0;
        moyH = 0;
      }
      
      String data = "";
      data = String(data + byte(humidity) ); 
      data = String(data + "|"); 
      data = String(data + tempC); 
      data = String(data + "|"); 
      data = String(data + tempF); 
      data = String(data + "|"); 
      data = String(data + moy);
      data = String(data + "|");       
      data = String(data + temp[0]);  
      data = String(data + "|"); 
      data = String(data + hum[0]);  
      data = String(data + "|"); 
      data = String(data + temp[1]);  
      data = String(data + "|"); 
      data = String(data + hum[1]);  
      data = String(data + "|"); 
      data = String(data + temp[2]);  
      data = String(data + "|"); 
      data = String(data + hum[2]);  
      data = String(data + "|"); 
      data = String(data + temp[3]);  
      data = String(data + "|"); 
      data = String(data + hum[3]);  
      data = String(data + "|"); 
      data = String(data + temp[4]);  
      data = String(data + "|"); 
      data = String(data + hum[4]);  
      data = String(data + "|"); 
      data = String(data + temp[5]);  
      data = String(data + "|"); 
      data = String(data + hum[5]);  
      data = String(data + "|"); 
      data = String(data + temp[6]);  
      data = String(data + "|"); 
      data = String(data + hum[6]);  
      data = String(data + "|"); 
      data = String(data + temp[7]);  
      data = String(data + "|"); 
      data = String(data + hum[7]);  
      data = String(data + "|"); 
      data = String(data + temp[8]);  
      data = String(data + "|"); 
      data = String(data + hum[8]);  
      data = String(data + "|"); 
      data = String(data + temp[9]);  
      data = String(data + "|"); 
      data = String(data + hum[9]);  
      data = String(data + "|"); 
      data = String(data + temp[10]);  
      data = String(data + "|"); 
      data = String(data + hum[10]);  
      data = String(data + "|"); 
      data = String(data + temp[11]);  
      data = String(data + "|"); 
      data = String(data + hum[11]);  
      data = String(data + "|"); 
      data = String(data + temp[12]);  
      data = String(data + "|"); 
      data = String(data + hum[12]);  
      data = String(data + "|"); 
      data = String(data + temp[13]);  
      data = String(data + "|"); 
      data = String(data + hum[13]);  
      data = String(data + "|"); 
      data = String(data + temp[14]);  
      data = String(data + "|"); 
      data = String(data + hum[14]);  
      data = String(data + "|"); 
      data = String(data + temp[15]);  
      data = String(data + "|"); 
      data = String(data + hum[15]);  
      data = String(data + "|"); 
      data = String(data + temp[16]);  
      data = String(data + "|"); 
      data = String(data + hum[16]);  
      data = String(data + "|"); 
      data = String(data + temp[17]);  
      data = String(data + "|"); 
      data = String(data + hum[17]);  
      data = String(data + "|"); 
      data = String(data + temp[18]);  
      data = String(data + "|"); 
      data = String(data + hum[18]);   
      data = String(data + "|"); 
      data = String(data + temp[19]);  
      data = String(data + "|"); 
      data = String(data + hum[19]); 

      webSocket.broadcastTXT(data); // send the data
      Serial.println(data); // display the data in the serial monitor
  
      // blink the status LED to show data has been sent
      digitalWrite(pinLED, HIGH); delay(50); digitalWrite(pinLED, LOW);
  }  
} // void updateSensors()