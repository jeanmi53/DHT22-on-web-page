// webSocketEvent is called when there is a websocket event
void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length){
    Serial.println("");
    Serial.print("WStype = ");   Serial.println(type);  
    Serial.print("WS payload = ");
    for(int i = 0; i < length; i++) { Serial.print((char) payload[i]); }
    Serial.println();
}