-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tiempo de generación: 31-05-2018 a las 11:02:59
-- Versión del servidor: 5.7.22-0ubuntu0.16.04.1
-- Versión de PHP: 7.0.30-0ubuntu0.16.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `gamedb`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters`
--

CREATE TABLE `characters` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(32) NOT NULL,
  `level` int(10) UNSIGNED NOT NULL,
  `XP` float UNSIGNED NOT NULL DEFAULT '0',
  `gold` int(10) UNSIGNED NOT NULL DEFAULT '0',
  `races_id_race` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `characters`
--

INSERT INTO `characters` (`id`, `name`, `level`, `XP`, `gold`, `races_id_race`) VALUES
(1, 'Jaime', 1, 0, 0, 2),
(2, 'Jesus', 1, 0, 0, 1),
(3, 'Anselmo', 1, 0, 668, 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters_inventories`
--

CREATE TABLE `characters_inventories` (
  `id` int(10) UNSIGNED NOT NULL,
  `inventories_id_inventory` int(10) UNSIGNED NOT NULL,
  `characters_id_character` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `characters_inventories`
--

INSERT INTO `characters_inventories` (`id`, `inventories_id_inventory`, `characters_id_character`) VALUES
(1, 1, 3),
(2, 5, 3),
(3, 5, 3),
(4, 4, 3),
(5, 3, 3),
(6, 2, 3),
(7, 5, 3),
(8, 5, 3),
(9, 4, 3);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `characters_users`
--

CREATE TABLE `characters_users` (
  `id` int(10) UNSIGNED NOT NULL,
  `users_id_user` int(10) UNSIGNED NOT NULL,
  `characters_id_character` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `characters_users`
--

INSERT INTO `characters_users` (`id`, `users_id_user`, `characters_id_character`) VALUES
(1, 2, 1),
(2, 2, 2),
(3, 9, 3);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `inventories`
--

CREATE TABLE `inventories` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(32) NOT NULL,
  `attack` float UNSIGNED NOT NULL,
  `defense` float UNSIGNED NOT NULL,
  `value` int(10) UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `inventories`
--

INSERT INTO `inventories` (`id`, `name`, `attack`, `defense`, `value`) VALUES
(1, 'EspadaTocha', 25, 0, 60),
(2, 'Trebol', 20, 35, 50),
(3, 'Escopeta', 65, 3, 70),
(4, 'Escudo', 0, 87, 100),
(5, 'Puño de Thanos', 1000, 1000, 10000);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `login`
--

CREATE TABLE `login` (
  `id` int(10) UNSIGNED NOT NULL,
  `users_id_user` int(10) UNSIGNED NOT NULL,
  `isConnected` bit(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `Maps`
--

CREATE TABLE `Maps` (
  `MapId` int(10) UNSIGNED NOT NULL,
  `MapName` varchar(32) NOT NULL,
  `MapContent` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Volcado de datos para la tabla `Maps`
--

INSERT INTO `Maps` (`MapId`, `MapName`, `MapContent`) VALUES
(1, 'Dungeon1', '<room squareAmountX="15" squareAmountY="20">\r\n	<square type="player" x="2" y="17" />\r\n	<square type="wall" x="0" y="0" />\r\n	<square type="wall" x="1" y="0" />\r\n	<square type="wall" x="2" y="0" />\r\n	<square type="wall" x="3" y="0" />\r\n	<square type="wall" x="10" y="0" />\r\n	<square type="wall" x="3" y="1" />\r\n	<square type="wall" x="10" y="1" />\r\n	<square type="wall" x="3" y="2" />\r\n	<square type="wall" x="10" y="2" />\r\n	<square type="wall" x="3" y="3" />\r\n	<square type="door" x="10" y="3" />\r\n	<square type="wall" x="3" y="4" />\r\n	<square type="door" x="10" y="4" />\r\n	<square type="wall" x="3" y="5" />\r\n	<square type="wall" x="10" y="5" />\r\n	<square type="wall" x="11" y="5" />\r\n	<square type="wall" x="12" y="5" />\r\n	<square type="wall" x="13" y="5" />\r\n	<square type="wall" x="14" y="5" />\r\n	<square type="wall" x="3" y="6" />\r\n	<square type="wall" x="3" y="7" />\r\n	<square type="wall" x="3" y="8" />\r\n	<square type="wall" x="3" y="9" />\r\n	<square type="wall" x="3" y="10" />\r\n	<square type="wall" x="3" y="11" />\r\n	<square type="wall" x="10" y="11" />\r\n	<square type="wall" x="3" y="12" />\r\n	<square type="wall" x="10" y="12" />\r\n	<square type="wall" x="3" y="13" />\r\n	<square type="wall" x="10" y="13" />\r\n	<square type="wall" x="10" y="14" />\r\n	<square type="wall" x="10" y="15" />\r\n	<square type="wall" x="11" y="15" />\r\n	<square type="wall" x="12" y="15" />\r\n	<square type="wall" x="13" y="15" />\r\n	<square type="wall" x="14" y="15" />\r\n	<square type="wall" x="10" y="16" />\r\n	<square type="wall" x="10" y="17" />\r\n	<square type="wall" x="7" y="18" />\r\n	<square type="wall" x="8" y="18" />\r\n	<square type="wall" x="9" y="18" />\r\n	<square type="wall" x="10" y="18" />\r\n	<square type="door" x="7" y="19" />\r\n	<square type="enemy" x="12" y="1" />\r\n	<square type="enemy" x="1" y="2" />\r\n	<square type="enemy" x="13" y="2" />\r\n	<square type="enemy" x="12" y="11" />\r\n	<square type="gold" x="14" y="0" />\r\n	<square type="gold" x="13" y="13" />\r\n	<square type="gold" x="13" y="17" />\r\n	<square type="gold" x="13" y="18" />\r\n</room>'),
(2, 'Dungeon2', '<room squareAmountX="6" squareAmountY="9">\r\n	<square type="player" x="2" y="9" />\r\n	<square type="wall" x="0" y="0" />\r\n	<square type="wall" x="1" y="0" />\r\n	<square type="wall" x="2" y="0" />\r\n	<square type="wall" x="3" y="0" />\r\n	<square type="wall" x="3" y="1" />\r\n	<square type="wall" x="3" y="2" />\r\n	<square type="wall" x="4" y="3" />\r\n	<square type="wall" x="4" y="4" />\r\n	<square type="wall" x="3" y="5" />\r\n	<square type="wall" x="3" y="6" />\r\n	<square type="wall" x="1" y="7" />\r\n	<square type="wall" x="1" y="8" />\r\n	<square type="wall" x="3" y="9" />\r\n	<square type="wall" x="2" y="0" />\r\n	<square type="wall" x="3" y="2" />\r\n	<square type="wall" x="1" y="2" />\r\n	<square type="wall" x="6" y="8" />\r\n	<square type="wall" x="6" y="8" />\r\n	<square type="wall" x="3" y="8" />\r\n	<square type="wall" x="1" y="8" />\r\n	<square type="door" x="5" y="9" />\r\n	<square type="enemy" x="5" y="1" />\r\n	<square type="enemy" x="5" y="2" />\r\n	<square type="enemy" x="5" y="3" />\r\n	<square type="enemy" x="4" y="1" />\r\n	<square type="gold" x="4" y="0" />\r\n	<square type="gold" x="3" y="3" />\r\n	<square type="gold" x="3" y="7" />\r\n	<square type="gold" x="3" y="1" />\r\n</room>'),
(3, 'Dungeon3', '<room squareAmountX="5" squareAmountY="5">\r\n	<square type="player" x="1" y="5" />\r\n	<square type="wall" x="2" y="4" />\r\n	<square type="wall" x="3" y="3" />\r\n	<square type="wall" x="4" y="2" />\r\n	<square type="door" x="5" y="1" />\r\n	<square type="enemy" x="5" y="0" />\r\n	<square type="enemy" x="4" y="0" />\r\n	<square type="enemy" x="3" y="1" />\r\n	<square type="enemy" x="2" y="2" />\r\n	<square type="gold" x="1" y="3" />\r\n	<square type="gold" x="0" y="4" />\r\n	<square type="gold" x="1" y="5" />\r\n	<square type="gold" x="2" y="5" />\r\n</room>');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `races`
--

CREATE TABLE `races` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(32) NOT NULL,
  `base_attack` float UNSIGNED NOT NULL,
  `base_defense` float UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `races`
--

INSERT INTO `races` (`id`, `name`, `base_attack`, `base_defense`) VALUES
(1, 'Elfo', 10, 5),
(2, 'Babuino', 4, 10);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `stats`
--

CREATE TABLE `stats` (
  `id` int(10) UNSIGNED NOT NULL,
  `characters_id_character` int(10) UNSIGNED NOT NULL,
  `attack` int(10) UNSIGNED NOT NULL,
  `defense` float UNSIGNED NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `stats`
--

INSERT INTO `stats` (`id`, `characters_id_character`, `attack`, `defense`) VALUES
(1, 1, 7, 5),
(2, 2, 4, 2),
(3, 3, 4, 2);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `users`
--

CREATE TABLE `users` (
  `id` int(10) UNSIGNED NOT NULL,
  `user` varchar(32) NOT NULL,
  `password` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `users`
--

INSERT INTO `users` (`id`, `user`, `password`) VALUES
(1, 'Jose', 'enti4212'),
(2, 'Pau', 'enti'),
(3, 'Marc', '1234'),
(9, 'Test', 'test');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `characters`
--
ALTER TABLE `characters`
  ADD PRIMARY KEY (`id`),
  ADD KEY `races_id_race` (`races_id_race`);

--
-- Indices de la tabla `characters_inventories`
--
ALTER TABLE `characters_inventories`
  ADD PRIMARY KEY (`id`),
  ADD KEY `inventories_id_inventory` (`inventories_id_inventory`),
  ADD KEY `characters_id_character` (`characters_id_character`);

--
-- Indices de la tabla `characters_users`
--
ALTER TABLE `characters_users`
  ADD PRIMARY KEY (`id`),
  ADD KEY `users_id_user` (`users_id_user`),
  ADD KEY `characters_id_character` (`characters_id_character`);

--
-- Indices de la tabla `inventories`
--
ALTER TABLE `inventories`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `login`
--
ALTER TABLE `login`
  ADD PRIMARY KEY (`id`),
  ADD KEY `users_id_user` (`users_id_user`);

--
-- Indices de la tabla `Maps`
--
ALTER TABLE `Maps`
  ADD PRIMARY KEY (`MapId`);

--
-- Indices de la tabla `races`
--
ALTER TABLE `races`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `stats`
--
ALTER TABLE `stats`
  ADD PRIMARY KEY (`id`),
  ADD KEY `characters_id_character` (`characters_id_character`);

--
-- Indices de la tabla `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `characters`
--
ALTER TABLE `characters`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT de la tabla `characters_inventories`
--
ALTER TABLE `characters_inventories`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
--
-- AUTO_INCREMENT de la tabla `characters_users`
--
ALTER TABLE `characters_users`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT de la tabla `inventories`
--
ALTER TABLE `inventories`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT de la tabla `login`
--
ALTER TABLE `login`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT de la tabla `Maps`
--
ALTER TABLE `Maps`
  MODIFY `MapId` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT de la tabla `races`
--
ALTER TABLE `races`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT de la tabla `stats`
--
ALTER TABLE `stats`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- AUTO_INCREMENT de la tabla `users`
--
ALTER TABLE `users`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `characters`
--
ALTER TABLE `characters`
  ADD CONSTRAINT `Characters_ibfk_1` FOREIGN KEY (`races_id_race`) REFERENCES `races` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `characters_inventories`
--
ALTER TABLE `characters_inventories`
  ADD CONSTRAINT `Characters_inventories_ibfk_1` FOREIGN KEY (`inventories_id_inventory`) REFERENCES `inventories` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `Characters_inventories_ibfk_2` FOREIGN KEY (`characters_id_character`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `characters_users`
--
ALTER TABLE `characters_users`
  ADD CONSTRAINT `Characters_users_ibfk_1` FOREIGN KEY (`users_id_user`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `Characters_users_ibfk_2` FOREIGN KEY (`characters_id_character`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `login`
--
ALTER TABLE `login`
  ADD CONSTRAINT `Login_ibfk_1` FOREIGN KEY (`users_id_user`) REFERENCES `users` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `stats`
--
ALTER TABLE `stats`
  ADD CONSTRAINT `Stats_ibfk_1` FOREIGN KEY (`characters_id_character`) REFERENCES `characters` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
