-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 02, 2023 at 08:40 AM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `team4`
--

-- --------------------------------------------------------

--
-- Table structure for table `table_rfid`
--

CREATE TABLE `table_rfid` (
  `id_session` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(255) NOT NULL,
  `created_at` datetime DEFAULT current_timestamp(),
  `name` varchar(100) NOT NULL,
  `id` varchar(100) NOT NULL,
  `gender` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `car` varchar(100) NOT NULL,
  `usertype` varchar(20) NOT NULL DEFAULT 'user',
  `status` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `table_rfid`
--

INSERT INTO `table_rfid` (`id_session`, `username`, `password`, `created_at`, `name`, `id`, `gender`, `email`, `car`, `usertype`, `status`) VALUES
(17, 'admin', '$2y$10$BwjCXpys1nUVOG32zo/g3e7Cp04VUqtb0xeaaF3GzGjJusk/ltinm', '2023-05-26 15:59:55', '', '', '', '', '', 'admin', 0),
(18, 'test', '$2y$10$SmJ4AHUSNoDWC6LilPEfeeS2Qg747IxVZGc2mpgNX9IskSS6kMexS', '2023-05-26 16:03:25', 'TestEuy', '123jsd123', 'Male', 'test@gmail.com', 'avanza', 'user', 1),
(19, 'test1', '$2y$10$..knWEuBk5.7GW/YswxkP.3u98t36BBp7hXiKd18tq5B6Quav7KRq', '2023-05-26 23:02:10', 'testtest', '123ads123', 'Male', 'testt@gmail.com', 'xenia', 'user', 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `table_rfid`
--
ALTER TABLE `table_rfid`
  ADD PRIMARY KEY (`id_session`),
  ADD UNIQUE KEY `username` (`username`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `table_rfid`
--
ALTER TABLE `table_rfid`
  MODIFY `id_session` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
