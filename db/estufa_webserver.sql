-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 08-Nov-2022 às 15:16
-- Versão do servidor: 10.4.24-MariaDB
-- versão do PHP: 7.4.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `estufa_webserver`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `dadosestufa`
--

CREATE TABLE `dadosestufa` (
  `id` int(11) NOT NULL,
  `estadoBomba` varchar(10) NOT NULL,
  `umidadeSolo` int(100) NOT NULL,
  `umidadeFora` varchar(5) NOT NULL,
  `temperaturaCFora` float NOT NULL,
  `temperaturaFFora` float NOT NULL,
  `umidadeDentro` varchar(5) NOT NULL,
  `temperaturaCDentro` float NOT NULL,
  `temperaturaFDentro` float NOT NULL,
  `tempo` timestamp(6) NOT NULL DEFAULT current_timestamp(6) ON UPDATE current_timestamp(6)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Índices para tabelas despejadas
--

--
-- Índices para tabela `dadosestufa`
--
ALTER TABLE `dadosestufa`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `dadosestufa`
--
ALTER TABLE `dadosestufa`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
