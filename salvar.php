<?php
include('conexao.php');

date_default_timezone_set('America/Sao_Paulo');

// $umidade = $_GET['umidade'];
// $temperatura = $_GET['temp'];

// $timezone = new DateTimeZone('America/Sao_Paulo');
// $data_hora = date('Y-m-d H:i');

// $sql = "INSERT INTO tbdata(umidade,temperatura,tempo) VALUES(:umidade, :temperatura, :tempo)";

// $stmt = $PDO->prepare($sql);

// $stmt->bindParam(':umidade',$umidade);
// $stmt->bindParam(':temperatura',$temperatura);
// $stmt->bindParam(':tempo',$data_hora);

// if($stmt->execute()){
//     echo "Data Success!";
// }else{
//     echo "Data Failure!";
// }

$estadoBomba = $_GET['estadoBomba'];//variavel que recebe se a bomba de água está ligado ou desligado
$umidadeSolo = $_GET['umidadeSolo'];//variavel que recebe a umidade do solo

$timezone = new DateTimeZone('America/Sao_Paulo');//pega data de São Paulo
$data_hora = date('Y-m-d H:i');//define padrão de data para inserir na tabela (Ano-Mes-Dia Hora:Minuto)

$sql = "INSERT INTO dadosEstufa(estadoBomba,umidadeSolo,tempo) VALUES(:estadoBomba, :umidadeSolo, :tempo)";//variavel sql que recebe um insert
$stmt = $PDO->prepare($sql);//executa insergravando dados na tabela

//variaveis para inserir no banco
$stmt->bindParam(':estadoBomba',$estadoBomba);
$stmt->bindParam(':umidadeSolo',$umidadeSolo);
$stmt->bindParam(':tempo',$data_hora);

//verifica se foi inserido com sucesso
if($stmt->execute()){
    echo "Data Success!";
}else{
    echo "Data Failure!";
}
?>