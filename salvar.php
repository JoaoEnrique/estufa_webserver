<?php
include('conexao.php');

date_default_timezone_set('America/Sao_Paulo');

$estadoBomba = $_GET['estadoBomba'];//variavel que recebe se a bomba de água está ligado ou desligado
$umidadeSolo = $_GET['umidadeSolo'];//variavel que recebe a umidade do solo

$umidadeFora = $_GET['umidadeFora'];//variavel que recebe a umidade de fora da estufa
$temperaturaCFora = $_GET['temperaturaCFora'];//variavel que recebe a temperatura em Celsius de fora da estufa
$temperaturaFFora = $_GET['temperaturaFFora'];//variavel que recebe a temperatura em Fahrenheit de fora da estufa

$umidadeDentro = $_GET['umidadeDentro'];//variavel que recebe a umidade de dentro da estufa
$temperaturaCDentro = $_GET['temperaturaCDentro'];//variavel que recebe a temperatura em Celsius de dentro da estufa
$temperaturaFDentro = $_GET['temperaturaFDentro'];//variavel que recebe a temperatura em Fahrenheit de dentro da estufa

$timezone = new DateTimeZone('America/Sao_Paulo');//pega data de São Paulo
$data_hora = date('Y-m-d H:i');//define padrão de data para inserir na tabela (Ano-Mes-Dia Hora:Minuto)

$sql = "INSERT INTO 
    dadosEstufa(estadoBomba,umidadeSolo,umidadeFora,temperaturaCFora,temperaturaFFora,umidadeDentro,temperaturaCDentro,temperaturaFDentro,tempo) 
    VALUES(:estadoBomba, :umidadeSolo, :umidadeFora, :temperaturaCFora, :temperaturaFFora, :umidadeDentro, :temperaturaCDentro, :temperaturaFDentro, :tempo)";//variavel sql que recebe um insert
$stmt = $PDO->prepare($sql);//executa insergravando dados na tabela

//variaveis para inserir no banco
$stmt->bindParam(':estadoBomba',$estadoBomba);
$stmt->bindParam(':umidadeSolo',$umidadeSolo);
$stmt->bindParam(':umidadeFora',$umidadeFora);
$stmt->bindParam(':temperaturaCFora',$temperaturaCFora);
$stmt->bindParam(':temperaturaFFora',$temperaturaFFora);
$stmt->bindParam(':umidadeDentro',$umidadeDentro);
$stmt->bindParam(':temperaturaCDentro',$temperaturaCDentro);
$stmt->bindParam(':temperaturaFDentro',$temperaturaFDentro);
$stmt->bindParam(':tempo',$data_hora);

//verifica se foi inserido com sucesso
if($stmt->execute()){
    echo "Data Success!";
}else{
    echo "Data Failure!";
}
?>