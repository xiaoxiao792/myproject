/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50140
Source Host           : localhost:3306
Source Database       : fruitshop

Target Server Type    : MYSQL
Target Server Version : 50140
File Encoding         : 65001

Date: 2019-12-03 21:47:29
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for cart
-- ----------------------------
DROP TABLE IF EXISTS `cart`;
CREATE TABLE `cart` (
  `cart_id` int(20) NOT NULL AUTO_INCREMENT,
  `user_id` int(20) NOT NULL,
  `goods_id` int(20) NOT NULL,
  `goods_num` int(10) NOT NULL DEFAULT '1',
  PRIMARY KEY (`cart_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10018 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of cart
-- ----------------------------
INSERT INTO `cart` VALUES ('10004', '10002', '10001', '4');
INSERT INTO `cart` VALUES ('10014', '10002', '10002', '1');
INSERT INTO `cart` VALUES ('10015', '10003', '10001', '1');
INSERT INTO `cart` VALUES ('10016', '10001', '10002', '1');
INSERT INTO `cart` VALUES ('10017', '10001', '10001', '1');

-- ----------------------------
-- Table structure for goods
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods` (
  `goods_id` int(20) NOT NULL AUTO_INCREMENT,
  `goods_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_unicode_ci NOT NULL,
  `goods_price` float(20,2) NOT NULL,
  `goods_class` int(10) NOT NULL,
  `goods_img` varchar(255) NOT NULL,
  PRIMARY KEY (`goods_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10003 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('10001', '水晶葡萄', '10.00', '1', 'goods.jpg');
INSERT INTO `goods` VALUES ('10002', '苹果', '20.00', '2', 'goods02.jpg');

-- ----------------------------
-- Table structure for order
-- ----------------------------
DROP TABLE IF EXISTS `order`;
CREATE TABLE `order` (
  `order_id` varchar(50) CHARACTER SET gbk NOT NULL,
  `user_id` int(20) NOT NULL,
  `goods_id` int(20) NOT NULL DEFAULT '10001',
  `goods_num` int(10) DEFAULT NULL,
  `order_stata` int(10) NOT NULL,
  `order_time` varchar(50) NOT NULL,
  `order_top` varchar(50) CHARACTER SET gbk DEFAULT '0',
  `order_price` float(20,2) NOT NULL,
  PRIMARY KEY (`order_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of order
-- ----------------------------
INSERT INTO `order` VALUES ('1', '10001', '10001', null, '1', '2019-12-03 12:27:19', '0', '30.00');
INSERT INTO `order` VALUES ('2', '10001', '10001', '1', '3', '2019-12-03 12:27:45', '1', '10.00');
INSERT INTO `order` VALUES ('20191203213737043480', '10001', '10001', null, '1', '2019-12-03 21:37:37', '0', '20.00');
INSERT INTO `order` VALUES ('20191203213737044511', '10001', '10002', '1', '1', '2019-12-03 21:37:37', '20191203213737043480', '20.00');
INSERT INTO `order` VALUES ('20191203214110089721', '10001', '10001', null, '1', '2019-12-03 21:41:10', '0', '20.00');
INSERT INTO `order` VALUES ('20191203214110091257', '10001', '10002', '1', '1', '2019-12-03 21:41:10', '20191203214110089721', '20.00');
INSERT INTO `order` VALUES ('20191203214133002721', '10001', '10001', null, '1', '2019-12-03 21:41:33', '0', '20.00');
INSERT INTO `order` VALUES ('20191203214133004482', '10001', '10002', '1', '1', '2019-12-03 21:41:33', '20191203214133002721', '20.00');
INSERT INTO `order` VALUES ('20191203214143090734', '10001', '10001', null, '1', '2019-12-03 21:41:43', '0', '30.00');
INSERT INTO `order` VALUES ('20191203214143092658', '10001', '10002', '1', '1', '2019-12-03 21:41:43', '20191203214143090734', '30.00');
INSERT INTO `order` VALUES ('20191203214143093961', '10001', '10001', '1', '1', '2019-12-03 21:41:43', '20191203214143090734', '30.00');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `user_id` int(20) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(50) NOT NULL,
  `user_passwd` varchar(50) NOT NULL,
  `user_power` int(10) NOT NULL,
  `user_email` varchar(50) NOT NULL DEFAULT '0',
  PRIMARY KEY (`user_id`)
) ENGINE=InnoDB AUTO_INCREMENT=10005 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('10001', '10001', '1', '1', '1');
INSERT INTO `user` VALUES ('10002', '10002', '2', '2', '2');
INSERT INTO `user` VALUES ('10003', '123456', '123456', '1', '123456@qq.com');
INSERT INTO `user` VALUES ('10004', '10003', '123456', '1', '2687863@qq.com');
