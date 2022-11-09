<?php
define('BD_SERVIDOR','localhost');
define('BD_USUARIO','root');
define('BD_SENHA','');
define('BD_BANCO','estufa_webserver');

class Listar{

    protected $mysqli;
    private $cadastro;

    public function __construct(){
        $this->conexao();
        if(isset($_GET['funcao']) && $_GET['funcao'] == "limparTabela"){
            $this->limparTabela();
        }
    }

    private function conexao(){
        $this->mysqli = new mysqli(BD_SERVIDOR, BD_USUARIO , BD_SENHA, BD_BANCO);
    }

    public function exibir(){
        try{
            $stmt = $this->mysqli->query("SELECT * FROM dadosEstufa;");
            $lista = $stmt->fetch_all(MYSQLI_ASSOC);
            $f_lista = array();
            $i = 0;
            foreach ($lista as $l){
                $f_lista[$i]['id'] = $l['id'];
                $f_lista[$i]['estadoBomba'] = $l['estadoBomba'];
                $f_lista[$i]['umidadeSolo'] = $l['umidadeSolo'];
                $f_lista[$i]['umidadeFora'] = $l['umidadeFora'];
                $f_lista[$i]['temperaturaCFora'] = $l['temperaturaCFora'];
                $f_lista[$i]['temperaturaFFora'] = $l['temperaturaFFora'];
                $f_lista[$i]['umidadeDentro'] = $l['umidadeDentro'];
                $f_lista[$i]['temperaturaCDentro'] = $l['temperaturaCDentro'];
                $f_lista[$i]['temperaturaFDentro'] = $l['temperaturaFDentro'];
                $f_lista[$i]['tempo'] = $l['tempo'];
                $i++;
            }
            return $f_lista;
        }catch(Exception $e){
            echo "Ocorreu um erro ao tentar buscar todos os dados" . $e;
        }
    }
    
    public function limparTabela(){
        try{
            $stmt = $this->mysqli->query("TRUNCATE dadosestufa;");
            echo "<script>alert('Tabela Limpa!');document.location='index.php'</script>";
        }catch(Exception $e){
            echo "Ocorreu um erro ao limpar tabela" . $e;
        }
    }
}
?>