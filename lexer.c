
Autoarr(Token)* lexan(char* source){
    Autoarr(Token)* tokens=malloc(sizeof(Autoarr(Token)));
    *tokens=Autoarr_create(Token,64,1024);
    char c;
    string label={source,0};
    
    void addlabel(){
        if(label.length!=0) return;
        Unitype token=ST_pull_str(label);
        if(token.type==Null){
            //custom token
        }
        Autoarr_add(tokens, (*token.VoidPtr));
        label={source,0};
    };
    
    addtok(TokenId id){
       Autoarr_add(tokens, default_tokens[id]);
    }
    
    while ((c=*source++)) switch(c){
        case ' ': case '\t':
        case '\r': case '\n':
                addlabel();
                break;
        case '(':
            addlabel();
            addtok(tok_lbracket);
            break;
            
            
    }
}
