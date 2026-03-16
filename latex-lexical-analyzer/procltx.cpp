#include <bits/stdc++.h>
using namespace std;
#include "lex.yy.c"

typedef struct _node {
   char *name;
   int cnt;
   struct _node *next;
} node;

typedef node *symboltable;

symboltable addtbl(symboltable T, char *id) {
   node *p = T;
   while (p) {
      if (!strcmp(p->name, id)) {
         p->cnt++;
         return T;
      }
      p = p->next;
   }
   p = (node *)malloc(sizeof(node));
   p->cnt=1;
   p->name = (char *)malloc((strlen(id) + 1) * sizeof(char));
   strcpy(p->name, id);
   p->next = T;
   return p;
}

int yywrap(){
   return 1;
}
int main() {
   int nextok;
   symboltable CMND = NULL;
   symboltable ENV = NULL;
   int m_e = 0;
   int d_e = 0;
   while ((nextok = yylex())) {
      switch (nextok) {
         case CMND_: CMND = addtbl(CMND, yytext); break;
         case ENVB: ENV = addtbl(ENV, yytext); break;
         case ENVE: break;
         case ME: m_e++; break;
         case DE: d_e++; break;
         default: break;
      }
   }

   cout << "Commands used:" << endl;
   symboltable temp_comm = CMND;
   while (temp_comm != NULL) {
       cout << "\t\\" << temp_comm->name << " (" << temp_comm->cnt << ")" << endl;
       temp_comm = temp_comm->next;
   }
   cout << "Environments used:" << endl;
   symboltable temp_env = ENV;
   while (temp_env != NULL) {
       cout << "\t" << temp_env->name << " (" << (temp_env->cnt) << ")" << endl;
       temp_env = temp_env->next;
   }
   cout << m_e/2 << " math equations found" << endl;
   cout << d_e/2 << " displayed equations found" << endl;
 
   return 0;
}