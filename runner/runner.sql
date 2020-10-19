/*
 Navicat Premium Data Transfer

 Source Server         : 手机端测试连接
 Source Server Type    : MySQL
 Source Server Version : 50173
 Source Host           : 192.168.0.108:3306
 Source Schema         : runner

 Target Server Type    : MySQL
 Target Server Version : 50173
 File Encoding         : 65001

 Date: 27/06/2020 21:15:15
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course` (
  `courseid` varchar(20) NOT NULL,
  `coursename` varchar(255) NOT NULL,
  `courseimg` varchar(255) NOT NULL,
  `coursevideo` varchar(255) NOT NULL,
  `coursetime` int(11) NOT NULL,
  `coursedescribe` varchar(255) NOT NULL,
  PRIMARY KEY (`courseid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of course
-- ----------------------------
BEGIN;
INSERT INTO `course` VALUES ('10001', '12分钟快乐燃脂运动', 'http://192.168.0.106/chfs/shared/runner/img/001.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/001.mp4', 12, '太欢乐啦！帕梅拉12分钟快乐燃脂运动！带你欢乐减脂！');
INSERT INTO `course` VALUES ('10002', '15分钟日常拉伸训练', 'http://192.168.0.106/chfs/shared/runner/img/002.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/002.mp4', 15, '帕梅拉15分钟日常拉伸训练，放松你的全身');
INSERT INTO `course` VALUES ('10003', '10分钟无跳跃有氧训练', 'http://192.168.0.106/chfs/shared/runner/img/003.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/003.mp4', 10, '帕梅拉10分钟无跳跃有氧训练！高效燃脂！');
INSERT INTO `course` VALUES ('10004', '12分钟中等强度腹部训练', 'http://192.168.0.106/chfs/shared/runner/img/004.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/004.mp4', 12, '魔鬼帕梅拉12分钟中等强度腹部训练，新手福音！');
INSERT INTO `course` VALUES ('10005', '15分钟瘦腿训练', 'http://192.168.0.106/chfs/shared/runner/img/005.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/005.mp4', 15, '大象腿有救了！帕梅拉15分钟瘦腿训练，紧实大腿内外侧！');
INSERT INTO `course` VALUES ('10006', '10分钟紧实手臂训练', 'http://192.168.0.106/chfs/shared/runner/img/006.jpeg', 'http://192.168.0.106/chfs/shared/runner/vedio/006.mp4', 10, '帕梅拉10分钟紧实手臂训练，在家用水壶就能瘦手臂啦！');
COMMIT;

-- ----------------------------
-- Table structure for coursesub
-- ----------------------------
DROP TABLE IF EXISTS `coursesub`;
CREATE TABLE `coursesub` (
  `coursesubid` varchar(20) NOT NULL,
  `courseid` varchar(20) NOT NULL,
  `coursesubnum` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`coursesubid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of coursesub
-- ----------------------------
BEGIN;
INSERT INTO `coursesub` VALUES ('10001', '10001', 98198);
INSERT INTO `coursesub` VALUES ('10002', '10002', 210425);
INSERT INTO `coursesub` VALUES ('10003', '10003', 53186);
INSERT INTO `coursesub` VALUES ('10004', '10004', 98154);
INSERT INTO `coursesub` VALUES ('10005', '10005', 155802);
INSERT INTO `coursesub` VALUES ('10006', '10006', 42967);
COMMIT;

-- ----------------------------
-- Table structure for exercise
-- ----------------------------
DROP TABLE IF EXISTS `exercise`;
CREATE TABLE `exercise` (
  `exerciseid` varchar(20) NOT NULL,
  `userid` varchar(20) NOT NULL,
  `exercisedate` date NOT NULL,
  `exercisenum` int(11) NOT NULL,
  `exercisetime` int(11) NOT NULL,
  PRIMARY KEY (`exerciseid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for step
-- ----------------------------
DROP TABLE IF EXISTS `step`;
CREATE TABLE `step` (
  `stepid` varchar(20) NOT NULL,
  `userid` varchar(20) NOT NULL,
  `stepnum` int(11) NOT NULL,
  `stepdate` date NOT NULL,
  PRIMARY KEY (`stepid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of step
-- ----------------------------
BEGIN;
INSERT INTO `step` VALUES ('10002', '13535249179', 5000, '2020-06-27');
INSERT INTO `step` VALUES ('10003', '13542323623', 4000, '2020-06-27');
INSERT INTO `step` VALUES ('10004', '15016661285', 20000, '2020-06-27');
INSERT INTO `step` VALUES ('20200627210520169002', '15915291130', 0, '2020-06-27');
INSERT INTO `step` VALUES ('20200627205146493048', '15915291130', 62, '2020-06-27');
COMMIT;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `userid` varchar(20) NOT NULL,
  `userpassword` varchar(255) NOT NULL,
  `username` varchar(255) DEFAULT NULL,
  `userimg` varchar(255) DEFAULT NULL,
  `userheight` double(6,5) DEFAULT NULL,
  `userweight` double(6,5) DEFAULT NULL,
  `userage` datetime DEFAULT NULL,
  `usersex` int(5) DEFAULT NULL COMMENT '0 man; 1 woman',
  PRIMARY KEY (`userid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user
-- ----------------------------
BEGIN;
INSERT INTO `user` VALUES ('15915291130', '123456', '张三', NULL, NULL, NULL, NULL, NULL);
COMMIT;

-- ----------------------------
-- Table structure for usersub
-- ----------------------------
DROP TABLE IF EXISTS `usersub`;
CREATE TABLE `usersub` (
  `usersubid` varchar(20) NOT NULL,
  `userid` varchar(20) NOT NULL,
  `courseid` varchar(20) NOT NULL,
  PRIMARY KEY (`usersubid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of usersub
-- ----------------------------
BEGIN;
INSERT INTO `usersub` VALUES ('10001', '15915291130', '10001');
INSERT INTO `usersub` VALUES ('10002', '15915291130', '10002');
INSERT INTO `usersub` VALUES ('10003', '13535249279', '10004');
INSERT INTO `usersub` VALUES ('20200627204800175041', '15915291130', '10004');
INSERT INTO `usersub` VALUES ('20200627205245573060', '15915291130', '10006');
COMMIT;

SET FOREIGN_KEY_CHECKS = 1;
