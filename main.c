#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sqlite3.h"

GtkStack *stack;
GtkBuilder *builder;
GtkWidget *window;
sqlite3 *db = 0;
int id = 0;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  int i;
  for (i = 0; i < argc; i++)
  {
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

void on_main_window_destroy(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_cadastrar_empresa_clicked(GtkWidget *widget, gpointer data)
{
  gtk_stack_set_visible_child_name(stack, "view_cadastro_empresa");
}

void mensagem(char text[100], char secondary_text[100], char icon_name[100])
{
  GtkDialog *dialog = GTK_DIALOG(gtk_builder_get_object(builder, "mensagem"));
  g_object_set(dialog, "secondary_text", secondary_text, NULL);
  g_object_set(dialog, "text", text, NULL);
  g_object_set(dialog, "icon_name", icon_name, NULL);
  gtk_widget_show_all(GTK_WIDGET(dialog));
  gtk_dialog_run(dialog);
  gtk_widget_hide(GTK_WIDGET(dialog));
}

void login(const char *email, const char *senha)
{
  g_print("Username : %s\n", email);
  g_print("Password : %s\n", senha);
  if ((strcmp(email, "admin") == 0) && (strcmp(senha, "admin") == 0))
  {
    mensagem("Bem vindo!", "Usuário logada com sucesso!", "emblem-default");
    gtk_stack_set_visible_child_name(stack, "view_menu_inicial");
  }
  else
  {
    mensagem("Aviso", "Email ou senha incorretos!", "dialog-error");
  }
}

static void on_button_login_clicked(GtkWidget *widget, gpointer data)
{
  GtkWidget *passwordInput;
  GtkWidget *usernameInput;
  passwordInput = GTK_WIDGET(gtk_builder_get_object(builder, "email"));
  usernameInput = GTK_WIDGET(gtk_builder_get_object(builder, "senha"));
  const char *email = gtk_entry_get_text(GTK_ENTRY(passwordInput));
  const char *senha = gtk_entry_get_text(GTK_ENTRY(usernameInput));
  login(email, senha);
}
void button_voltar_tela_cadastro_empresa_clicked(GtkWidget *widget, gpointer data)
{
  gtk_stack_set_visible_child_name(stack, "view_login");
}
void button_salvar_empresa_clicked(GtkWidget *widget, gpointer data)
{

  char *zErrMsg = 0;
  int rc;
  char *sql;
  GtkWidget *nomeEmpresaInput;
  GtkWidget *nomeResponsavelEmpresaInput;
  GtkWidget *cpfResponsavelEmpresaInput;
  GtkWidget *cnpjEmpresaInput;
  GtkWidget *razaoSocialEmpresaInput;
  GtkWidget *nomeFantasiaEmpresaInput;
  GtkWidget *telefoneEmpresaInput;
  GtkWidget *ruaEmpresaInput;
  GtkWidget *numeroEmpresaInput;
  GtkWidget *bairroEmpresaInput;
  GtkWidget *cidadeEmpresaInput;
  GtkWidget *estadoEmpresaInput;
  GtkWidget *cepEmpresaInput;
  GtkWidget *emailEmpresaInput;
  GtkWidget *senhaEmpresaInput;

  nomeEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "nome_empresa"));
  nomeResponsavelEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "nome_responsavel_empresa"));
  cpfResponsavelEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "cpf_responsavel_empresa"));
  cnpjEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "cnpj_empresa"));
  razaoSocialEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "razao_social_empresa"));
  nomeFantasiaEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "nome_fantasia_empresa"));
  telefoneEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "telefone_empresa"));
  ruaEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "rua_empresa"));
  numeroEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "numero_empresa"));
  bairroEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "bairro_empresa"));
  cidadeEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "cidade_empresa"));
  estadoEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "estado_empresa"));
  cepEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "cep_empresa"));
  emailEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "email_empresa"));
  senhaEmpresaInput = GTK_WIDGET(gtk_builder_get_object(builder, "senha_empresa"));

  const char *nomeEmpresa = gtk_entry_get_text(GTK_ENTRY(nomeEmpresaInput));
  const char *nomeResponsavel = gtk_entry_get_text(GTK_ENTRY(nomeResponsavelEmpresaInput));
  const char *cpfReponsavel = gtk_entry_get_text(GTK_ENTRY(cpfResponsavelEmpresaInput));
  const char *cnpjEmpresa = gtk_entry_get_text(GTK_ENTRY(cnpjEmpresaInput));
  const char *razaoSocialEmpresa = gtk_entry_get_text(GTK_ENTRY(razaoSocialEmpresaInput));
  const char *nomeFantasiaEmpresa = gtk_entry_get_text(GTK_ENTRY(nomeFantasiaEmpresaInput));
  const char *telefoneEmpresa = gtk_entry_get_text(GTK_ENTRY(telefoneEmpresaInput));
  const char *ruaEmpresa = gtk_entry_get_text(GTK_ENTRY(ruaEmpresaInput));
  const char *numeroEmpresa = gtk_entry_get_text(GTK_ENTRY(numeroEmpresaInput));
  const char *bairroEmpresa = gtk_entry_get_text(GTK_ENTRY(bairroEmpresaInput));
  const char *cidadeEmpresa = gtk_entry_get_text(GTK_ENTRY(cidadeEmpresaInput));
  const char *estadoEmpresa = gtk_entry_get_text(GTK_ENTRY(estadoEmpresaInput));
  const char *cepEmpresa = gtk_entry_get_text(GTK_ENTRY(cepEmpresaInput));
  const char *emailEmpresa = gtk_entry_get_text(GTK_ENTRY(emailEmpresaInput));
  const char *senhaEmpresa = gtk_entry_get_text(GTK_ENTRY(senhaEmpresaInput));

  if (strcmp(nomeEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Nome' obrigatório!", "dialog-error");
  }
  if (strcmp(nomeResponsavel, "") == 0)
  {
    mensagem("Aviso", "Campo 'Nome do responsável' obrigatório!", "dialog-error");
  }
  if (strcmp(cpfReponsavel, "") == 0)
  {
    mensagem("Aviso", "Campo 'Cpf' obrigatório!", "dialog-error");
  }
  if (strcmp(cnpjEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'CNPJ' obrigatório!", "dialog-error");
  }
  if (strcmp(razaoSocialEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Razao Social' obrigatório!", "dialog-error");
  }
  if (strcmp(nomeFantasiaEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Nome Fantasia' obrigatório!", "dialog-error");
  }
  if (strcmp(telefoneEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Telefone' obrigatório!", "dialog-error");
  }
  if (strcmp(ruaEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Rua' obrigatório!", "dialog-error");
  }
  if (strcmp(numeroEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Numero' obrigatório!", "dialog-error");
  }
  if (strcmp(bairroEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Bairro' obrigatório!", "dialog-error");
  }
  if (strcmp(cidadeEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Cidade' obrigatório!", "dialog-error");
  }
  if (strcmp(estadoEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Estado' obrigatório!", "dialog-error");
  }
  if (strcmp(cepEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Cep' obrigatório!", "dialog-error");
  }
  if (strcmp(emailEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Email' obrigatório!", "dialog-error");
  }
  if (strcmp(senhaEmpresa, "") == 0)
  {
    mensagem("Aviso", "Campo 'Senha' obrigatório!", "dialog-error");
  }

  sqlite3_stmt *handle_sql = 0;

  char sqlStr[256];

  char comando_sql[] = "INSERT INTO tb_empresa(nomeEmpresa, nomeResponsavel, cpfReponsavel, cnpj, razaoSocial, nomeFantasia, telefone, rua, numero, bairro, cidade, estado, cep, email, senha) VALUES ( ?, ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ?, ?)";

  rc = sqlite3_prepare_v2(db, comando_sql, -1, &handle_sql, 0);

  if (rc != SQLITE_OK)
  {
    printf("Erro no prepare : %s\n", sqlite3_errmsg(db));
    mensagem("Aviso", "Ocorreu um erro!", "dialog-emblem-deafult");
  }
  else
  {

    // telefone, rua, numero, bairro, cidade, estado, cep, email, senha
    rc = sqlite3_bind_text(handle_sql, 1, nomeEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 2, nomeResponsavel, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 3, cpfReponsavel, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 4, cnpjEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 5, razaoSocialEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 6, nomeFantasiaEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 7, telefoneEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 8, ruaEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 9, numeroEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 10, bairroEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 11, cidadeEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 12, estadoEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 13, cepEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 14, emailEmpresa, -1, NULL);
    rc = sqlite3_bind_text(handle_sql, 15, senhaEmpresa, -1, NULL);

    if (rc != SQLITE_OK)
    {
      printf("Erro no prepare : %s\n", sqlite3_errmsg(db));
      mensagem("Aviso", "Ocorreu um erro!", "dialog-emblem-deafult");
    }
    else
    {
      rc = sqlite3_step(handle_sql);
      mensagem("Aviso", "Empresa criada om sucesso", "dialog-emblem-deafult");
    }
  }
}

void button_relatorios_clicked(GtkWidget *widget, gpointer data)
{
  gtk_stack_set_visible_child_name(stack, "view_dados_empresa");
}
void button_gerenciar_empresa_clicked(GtkWidget *widget, gpointer data)
{
  gtk_stack_set_visible_child_name(stack, "view_gerenciar_empresa");
}
void button_sair_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_gerar_relatorio_geral_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_gerar_relatorio_maior_producao_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_gerar_relatorio_menor_producao_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_return_home_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_dados_empresa_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_list_funcionarios_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_list_clientes_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_gastos_residuos_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
void button_return_to_home_clicked(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}

void initializeSqlite()
{
  char *zErrMsg = 0;
  char *sql;

  int rc = sqlite3_open("database.db3", &db);

  if (rc != SQLITE_OK)
  {
    printf("Erro ao abrir.");
    sqlite3_close(db);
  }

  sql = "CREATE TABLE tb_empresa("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nomeEmpresa           TEXT    NOT NULL,"
        "nomeResponsavel           TEXT    NOT NULL,"
        "cpfReponsavel           TEXT    NOT NULL,"
        "cnpj           TEXT    NOT NULL,"
        "razaoSocial           TEXT    NOT NULL,"
        "nomeFantasia           TEXT    NOT NULL,"
        "telefone           TEXT    NOT NULL,"
        "rua           TEXT    NOT NULL,"
        "numero           TEXT    NOT NULL,"
        "bairro           TEXT    NOT NULL,"
        "cidade           TEXT    NOT NULL,"
        "estado           TEXT    NOT NULL,"
        "cep           TEXT    NOT NULL,"
        "email           TEXT    NOT NULL,"
        "senha           TEXT    NOT NULL);";

  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if (rc != SQLITE_OK)
  {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  else
  {
    fprintf(stdout, "Table created successfully\n");
  }
}

int main(int argc, char *argv[])
{

  gtk_init(&argc, &argv);

  // Carregamento da interface do glade
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "ui.glade", NULL);

  initializeSqlite();

  gtk_builder_add_callback_symbols(
      builder,
      "on_main_window_destroy", G_CALLBACK(on_main_window_destroy),
      "button_cadastrar_empresa_clicked", G_CALLBACK(button_cadastrar_empresa_clicked),
      "on_button_login_clicked", G_CALLBACK(on_button_login_clicked),
      "button_voltar_tela_cadastro_empresa_clicked", G_CALLBACK(button_voltar_tela_cadastro_empresa_clicked),
      "button_salvar_empresa_clicked", G_CALLBACK(button_salvar_empresa_clicked),
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
      NULL);

  GtkWidget *connectButton;
  gtk_builder_connect_signals(builder, NULL);
  stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
  window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));

  gtk_widget_show(window);
  gtk_main();
  sqlite3_close(db);

  return 0;
}
