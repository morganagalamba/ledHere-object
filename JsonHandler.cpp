/*void setup() {
  // put your setup code here, to run once:


    String colors[4][3];
    String effect = "";
    String token = "";
    String json ="{\"ColorSetup\":[[0,0,255],[0,12,255],[19,146,250],[255,0,0]],\"Effect\":\"324\", \"Token\":\"A23as5asdLKASDASJ24450askdaknsd\"}";
    //json.replace( json.begin(), json.end(), "{", "");
    // ---------Array de cores ---------
    json.replace("{", "");
    json.replace("}", "");
    String array = json.substring(json.indexOf("[[")+1,json.indexOf("]]") - json.indexOf("[["));
    int x = 0;
    int y = 0;
    for (int i = 0; i < array.length(); i++){
        if(array[i]!='[' && array[i]!=']' && array[i]!=','){
            colors[x][y] = colors[x][y] + array[i];
        }
        if(array[i] == ','){a
            y=y+1;
        }
        if(i>0 & array[i]=='['){
            x=x+1;
            y=0;
        }
    }
    //-------------Effect---------------
    
    for(int i = json.indexOf("\"Effect\":\"")+10; i < json.length(); i++){
        if(json[i]!='"'){
            effect = effect + json[i];
        }else{
            break;
        }   
    }
    //-------------Token---------------
    for(int i = json.indexOf("\"Token\":\"")+9; i < json.length(); i++){
        if(json[i]!='"'){
            token = token + json[i];
        }else{
            break;
        }   
    }
    //cout << effect;
    //cout << "\n";
    //cout << token;
    return 0;

}

void loop() {
  // put your main code here, to run repeatedly:

}*/
