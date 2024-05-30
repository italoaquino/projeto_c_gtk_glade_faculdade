#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>

GtkBuilder      *builder; 
GtkWidget       *window;

void on_main_window_destroy(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_cadastrar_empresa_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}

void mensagem(char text[100], char secondary_text[100], char icon_name[100]){
  GtkMessageDialog *mensagem_dialogo;
  mensagem_dialogo = GTK_WIDGET(gtk_builder_get_object(builder, "mensagem"));
  g_object_set (mensagem_dialogo, "text", text, NULL);
  g_object_set (mensagem_dialogo, "secondary_text", secondary_text, NULL);
  g_object_set (mensagem_dialogo,"icco_name", icon_name, NULL);
  gtk_widget_show_all (mensagem_dialogo);
  gtk_dialog_run(mensagem_dialogo);
  gtk_widget_hide(mensagem_dialogo);
}

void login(char *email, char *senha){
  if((strcmp(email, "admin")  == 0) && (strcmp(senha, "senha")  == 0)){
    mensagem("Bem vindo!", "Usuário empresa logada com sucesso!", "emblem-default");
  }else{
    mensagem("Aviso", "Email ou senha incorretos!", "dialog-error");
  }
}

static void on_button_login_clicked(GtkWidget *widget, gpointer data){
    GtkWidget *passwordInput;
    GtkWidget *usernameInput;

    passwordInput = GTK_WIDGET(gtk_builder_get_object(builder, "email"));
    usernameInput = GTK_WIDGET(gtk_builder_get_object(builder, "senha"));

    const gchar *text1 = gtk_entry_get_text(GTK_ENTRY(passwordInput));
    const gchar *text2 = gtk_entry_get_text(GTK_ENTRY(usernameInput));

    g_print("Username : %s\n",text2);
    g_print("Password : %s\n",text1);
}
void button_voltar_tela_cadastro_empresa_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_salvar_empresa_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_relatorios_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_gerenciar_empresa_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_sair_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_gerar_relatorio_geral_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_gerar_relatorio_maior_producao_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_gerar_relatorio_menor_producao_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_return_home_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_dados_empresa_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_list_funcionarios_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_list_clientes_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_gastos_residuos_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}
void button_return_to_home_clicked(GtkWidget *widget, gpointer data){
  gtk_main_quit();
}

int main (int argc, char *argv[]) {
  

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "ui.glade", NULL);


    gtk_builder_add_callback_symbols(
      builder,
      "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
      "button_cadastrar_empresa_clicked", G_CALLBACK(button_cadastrar_empresa_clicked),
      "on_button_login_clicked",G_CALLBACK(on_button_login_clicked),
      "button_voltar_tela_cadastro_empresa_clicked", G_CALLBACK(button_voltar_tela_cadastro_empresa_clicked),
      "button_salvar_empresa_clicked",G_CALLBACK(button_salvar_empresa_clicked),
      "button_relatorios_clicked", G_CALLBACK(button_relatorios_clicked),
      "button_gerenciar_empresa_clicked", G_CALLBACK(button_gerenciar_empresa_clicked),
      "button_sair_clicked", G_CALLBACK(button_sair_clicked),
      "button_gerar_relatorio_geral_clicked", G_CALLBACK(button_gerar_relatorio_geral_clicked),
      "button_gerar_relatorio_maior_producao_clicked", G_CALLBACK(button_gerar_relatorio_maior_producao_clicked),
      "button_gerar_relatorio_menor_producao_clicked", G_CALLBACK(button_gerar_relatorio_menor_producao_clicked),
      "button_return_home_clicked", G_CALLBACK(button_return_home_clicked),
      "button_dados_empresa_clicked", G_CALLBACK(button_dados_empresa_clicked),
      "button_list_funcionarios_clicked", G_CALLBACK(button_list_funcionarios_clicked),
      "button_list_clientes_clicked", G_CALLBACK(button_list_clientes_clicked),
      "button_gastos_residuos_clicked", G_CALLBACK(button_gastos_residuos_clicked),
      "button_return_to_home_clicked", G_CALLBACK(button_return_to_home_clicked),
      NULL
    );

    GtkWidget *connectButton;

    gtk_builder_connect_signals(builder, NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}


