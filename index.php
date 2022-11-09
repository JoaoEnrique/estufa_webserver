<?php
    require_once("model/listar.php");
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Estufa com WebServer e Esp32</title>
    <link rel="stylesheet" href="css/style.css">
    <script>
		function confirmarLimpeza(delUrl) {
  			if (confirm("Deseja limpar toda a tabela?")) {
   				document.location = delUrl;
	        }  
		}
    </script>
</head>
<body>
    <h1>Estufa com WebServer e Esp32</h1>
    <button name="btnLimparTabela" onclick="javascript:confirmarLimpeza('limparTabela.php?funcao=limparTabela')" type="submit" class="btn-limpar">Limpar Tabela</button>
    <button name="btnAtualizar" type="submit" class="btn-limpar"><a href="" class="link-atualizar">Atualizar Tabela</a></button>
    <table class="table">
        <thead>
            <tr>
                <th scope="col">Id</th>
                <th scope="col">Estado da Bomba</th>
                <th scope="col">Umidade do Solo</th>
                <th scope="col">Umidade fora da Estufa</th>
                <th scope="col">Temperatura fora da Estufa (°C)</th>
                <th scope="col">Temperatura fora da Estufa (°F)</th>
                
                <th scope="col">Umidade dentro da Estufa</th>
                <th scope="col">Temperatura dentro da Estufa (°C)</th>
                <th scope="col">Temperatura dentro da Estufa (°F)</th>
                <th scope="col">Data da Gravação</th>
            </tr>
        </thead>
        <tbody id='TableData'>
            <?php
                $listar = new Listar();
                $resultado = $listar->exibir();
                //print("ola");
                //echo $resultado[].length;
                for($i=0; $i<count($resultado); $i++){
            ?>
                    <tr class="row-table">
                        <td scope="col"><?php echo $resultado[$i]['id'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['estadoBomba'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['umidadeSolo'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['umidadeFora'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['temperaturaCFora'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['temperaturaFFora'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['umidadeDentro'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['temperaturaCDentro'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['temperaturaFDentro'];?></td>
                        <td scope="col"><?php echo $resultado[$i]['tempo'];?></td>
                    </tr>
            <?php
                }
            ?>
        </tbody>
    </table>
</body>
</html>