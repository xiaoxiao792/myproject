/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 80013
Source Host           : localhost:3306
Source Database       : hotel

Target Server Type    : MYSQL
Target Server Version : 80013
File Encoding         : 65001

Date: 2019-04-11 13:30:35
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `client`
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client` (
  `clientid` int(5) NOT NULL AUTO_INCREMENT,
  `clientclassid` int(5) NOT NULL,
  `clientsex` int(5) NOT NULL DEFAULT '0' COMMENT '0鐞涖劎銇氶悽鍑ょ礉1鐞涖劎銇氭總?',
  `clientphone` char(11) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `clientaddress` char(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `clientidnumber` char(18) NOT NULL,
  `clientname` char(20) NOT NULL,
  `clientemail` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `clientage` int(5) NOT NULL,
  PRIMARY KEY (`clientid`),
  UNIQUE KEY `clientidnumber` (`clientidnumber`) USING BTREE,
  UNIQUE KEY `clientphone` (`clientphone`) USING BTREE,
  KEY `clientclassid` (`clientclassid`),
  KEY `clientname` (`clientname`) USING BTREE,
  CONSTRAINT `client_ibfk_1` FOREIGN KEY (`clientclassid`) REFERENCES `clientclass` (`clientclassid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10004 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of client
-- ----------------------------
INSERT INTO `client` VALUES ('10001', '10001', '0', '13515261425', '广东广州', '440985199512050086', '张三', '489645498@qq.com', '23');
INSERT INTO `client` VALUES ('10002', '10002', '0', '13514781596', '广东广州', '440987199612230046', '李四', '4634135216@qq.com', '22');
INSERT INTO `client` VALUES ('10003', '10001', '0', '13514561236', '广东广州', '440923199612250078', '李二', '51256481@qq.com', '22');

-- ----------------------------
-- Table structure for `clientclass`
-- ----------------------------
DROP TABLE IF EXISTS `clientclass`;
CREATE TABLE `clientclass` (
  `clientclassid` int(5) NOT NULL,
  `clientclassname` char(20) NOT NULL,
  `discount` double(3,2) NOT NULL,
  PRIMARY KEY (`clientclassid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of clientclass
-- ----------------------------
INSERT INTO `clientclass` VALUES ('10001', '普通用户', '1.00');
INSERT INTO `clientclass` VALUES ('10002', 'vip1用户', '0.95');
INSERT INTO `clientclass` VALUES ('10003', 'vip2用户', '0.90');
INSERT INTO `clientclass` VALUES ('10004', 'vip3用户', '0.80');

-- ----------------------------
-- Table structure for `orderdb`
-- ----------------------------
DROP TABLE IF EXISTS `orderdb`;
CREATE TABLE `orderdb` (
  `orderid` int(10) NOT NULL AUTO_INCREMENT,
  `clientid` int(5) NOT NULL,
  `roomnum` int(5) NOT NULL DEFAULT '1',
  `roomid` int(5) NOT NULL,
  `orderdays` int(5) NOT NULL,
  `orderbegintime` datetime NOT NULL DEFAULT '0001-01-01 00:00:00',
  `orderendtine` datetime DEFAULT '0001-01-01 00:00:00',
  `orderprices` double(10,2) DEFAULT NULL,
  `orderstata` int(5) NOT NULL,
  `powerid` char(5) NOT NULL,
  `remark` char(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`orderid`),
  KEY `roomid` (`roomid`),
  KEY `order_ibfk_1` (`clientid`),
  KEY `powerid` (`powerid`),
  CONSTRAINT `orderdb_ibfk_1` FOREIGN KEY (`clientid`) REFERENCES `client` (`clientid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `orderdb_ibfk_2` FOREIGN KEY (`roomid`) REFERENCES `room` (`roomid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `orderdb_ibfk_3` FOREIGN KEY (`powerid`) REFERENCES `power` (`powerid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=10005 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of orderdb
-- ----------------------------
INSERT INTO `orderdb` VALUES ('10001', '10001', '1', '101', '1', '2019-04-01 19:35:07', '0001-01-01 00:00:00', null, '1', '10001', null);
INSERT INTO `orderdb` VALUES ('10002', '10003', '1', '201', '1', '2019-04-01 19:36:17', '0001-01-01 00:00:00', null, '1', '10001', '');
INSERT INTO `orderdb` VALUES ('10003', '10001', '1', '101', '1', '2019-04-01 19:54:17', '0001-01-01 00:00:00', null, '1', '10001', '');
INSERT INTO `orderdb` VALUES ('10004', '10003', '1', '203', '1', '2019-04-01 22:51:49', '0001-01-01 00:00:00', null, '2', '10001', '');

-- ----------------------------
-- Table structure for `power`
-- ----------------------------
DROP TABLE IF EXISTS `power`;
CREATE TABLE `power` (
  `powerid` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `powername` char(20) NOT NULL,
  `pwd` char(20) NOT NULL,
  PRIMARY KEY (`powerid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of power
-- ----------------------------
INSERT INTO `power` VALUES ('10001', '小红', '123456');
INSERT INTO `power` VALUES ('10002', '张丽', '123456');

-- ----------------------------
-- Table structure for `reserve`
-- ----------------------------
DROP TABLE IF EXISTS `reserve`;
CREATE TABLE `reserve` (
  `reserveid` int(10) NOT NULL AUTO_INCREMENT,
  `clientid` int(5) NOT NULL,
  `roomnum` int(5) NOT NULL DEFAULT '1',
  `isroom` int(5) NOT NULL,
  `roomid` int(5) NOT NULL,
  `reservedays` int(5) DEFAULT NULL,
  `reservetime` datetime NOT NULL DEFAULT '0001-01-01 00:00:00',
  `starttime` datetime NOT NULL DEFAULT '0001-01-01 00:00:00',
  `reservestata` int(5) NOT NULL,
  `powerid` char(5) NOT NULL,
  `remark` char(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`reserveid`),
  KEY `clientid` (`clientid`),
  KEY `roomid` (`roomid`),
  KEY `powerid` (`powerid`),
  CONSTRAINT `reserve_ibfk_1` FOREIGN KEY (`clientid`) REFERENCES `client` (`clientid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `reserve_ibfk_2` FOREIGN KEY (`roomid`) REFERENCES `room` (`roomid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `reserve_ibfk_3` FOREIGN KEY (`powerid`) REFERENCES `power` (`powerid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of reserve
-- ----------------------------

-- ----------------------------
-- Table structure for `room`
-- ----------------------------
DROP TABLE IF EXISTS `room`;
CREATE TABLE `room` (
  `roomid` int(5) NOT NULL,
  `roomclassid` int(5) NOT NULL,
  `roomfloor` int(5) NOT NULL,
  `roomstata` int(5) NOT NULL,
  PRIMARY KEY (`roomid`),
  KEY `roomclassid` (`roomclassid`),
  CONSTRAINT `roomclassid` FOREIGN KEY (`roomclassid`) REFERENCES `roomclass` (`roomclassid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of room
-- ----------------------------
INSERT INTO `room` VALUES ('101', '10001', '1', '1');
INSERT INTO `room` VALUES ('102', '10002', '1', '2');
INSERT INTO `room` VALUES ('103', '10003', '1', '1');
INSERT INTO `room` VALUES ('104', '10004', '1', '1');
INSERT INTO `room` VALUES ('105', '10005', '1', '1');
INSERT INTO `room` VALUES ('106', '10006', '1', '1');
INSERT INTO `room` VALUES ('201', '10001', '2', '2');
INSERT INTO `room` VALUES ('202', '10002', '2', '1');
INSERT INTO `room` VALUES ('203', '10003', '2', '3');
INSERT INTO `room` VALUES ('204', '10004', '2', '6');

-- ----------------------------
-- Table structure for `roomclass`
-- ----------------------------
DROP TABLE IF EXISTS `roomclass`;
CREATE TABLE `roomclass` (
  `roomclassid` int(5) NOT NULL,
  `roomclassname` char(20) NOT NULL,
  `roomprice` double(10,2) NOT NULL,
  PRIMARY KEY (`roomclassid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of roomclass
-- ----------------------------
INSERT INTO `roomclass` VALUES ('10001', '标准单人房', '150.00');
INSERT INTO `roomclass` VALUES ('10002', '标准双人房', '180.00');
INSERT INTO `roomclass` VALUES ('10003', '豪华单人房', '250.00');
INSERT INTO `roomclass` VALUES ('10004', '豪华双人房', '280.00');
INSERT INTO `roomclass` VALUES ('10005', '商务套房', '380.00');
INSERT INTO `roomclass` VALUES ('10006', '总统套房', '480.00');

-- ----------------------------
-- View structure for `clientdata`
-- ----------------------------
DROP VIEW IF EXISTS `clientdata`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`%` SQL SECURITY DEFINER VIEW `clientdata` AS select `client`.`clientid` AS `客户id`,`client`.`clientname` AS `客户`,`client`.`clientidnumber` AS `身份证`,`client`.`clientsex` AS `性别`,`client`.`clientage` AS `年龄`,`client`.`clientphone` AS `手机号码`,`client`.`clientemail` AS `邮箱地址`,`client`.`clientaddress` AS `客户住址`,`clientclass`.`clientclassname` AS `会员等级` from (`client` join `clientclass` on((`client`.`clientclassid` = `clientclass`.`clientclassid`))) ;

-- ----------------------------
-- View structure for `orderdata`
-- ----------------------------
DROP VIEW IF EXISTS `orderdata`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`%` SQL SECURITY DEFINER VIEW `orderdata` AS select `orderdb`.`orderid` AS `订单编号`,`client`.`clientname` AS `客户`,`orderdb`.`orderbegintime` AS `开房时间`,`client`.`clientphone` AS `手机号码`,`client`.`clientemail` AS `邮箱地址`,`orderdb`.`orderdays` AS `预住天数`,`orderdb`.`roomnum` AS `间数`,`room`.`roomid` AS `房间号`,`orderdb`.`orderstata` AS `状态`,`orderdb`.`remark` AS `备注` from ((`orderdb` join `client` on((`orderdb`.`clientid` = `client`.`clientid`))) join `room` on((`orderdb`.`roomid` = `room`.`roomid`))) ;

-- ----------------------------
-- View structure for `reservedata`
-- ----------------------------
DROP VIEW IF EXISTS `reservedata`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`%` SQL SECURITY DEFINER VIEW `reservedata` AS select `reserve`.`reserveid` AS `预定编号`,`client`.`clientname` AS `预定客户`,`reserve`.`reservetime` AS `预约时间`,`client`.`clientphone` AS `手机号码`,`client`.`clientemail` AS `邮箱地址`,`reserve`.`starttime` AS `预抵日期`,`reserve`.`reservedays` AS `预约天数`,`reserve`.`isroom` AS `排房`,`reserve`.`roomnum` AS `间数`,`room`.`roomid` AS `房间号`,`reserve`.`reservestata` AS `状态`,`reserve`.`remark` AS `备注` from ((`reserve` join `client` on((`reserve`.`clientid` = `client`.`clientid`))) join `room` on((`reserve`.`roomid` = `room`.`roomid`))) ;

-- ----------------------------
-- View structure for `roomdata`
-- ----------------------------
DROP VIEW IF EXISTS `roomdata`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`%` SQL SECURITY DEFINER VIEW `roomdata` AS select `room`.`roomid` AS `房间号`,`roomclass`.`roomclassid` AS `房间类型`,`room`.`roomfloor` AS `楼层`,`room`.`roomstata` AS `状态`,`roomclass`.`roomprice` AS `价格` from (`room` join `roomclass` on((`room`.`roomclassid` = `roomclass`.`roomclassid`))) ;
