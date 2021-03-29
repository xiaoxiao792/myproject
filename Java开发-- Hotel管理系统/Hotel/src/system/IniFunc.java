/**
 *##############################################################################
 *
 *	[ ģ����      ]  : ����INI�ļ�����ز���
 *	[ �ļ���      ]  : IniFunc.java
 *	[ ����ļ�    ]  : config.ini
 *	[ �ļ�ʵ�ֹ���]  : ��ȡ�ͱ���INI�ļ�
 *	[ ����        ]  : ���ı� 
 *	[ �汾        ]  : 1.0
 *	----------------------------------------------------------------------------
 *	[ ��ע        ]  : 
 *	----------------------------------------------------------------------------
 *	[ �޸ļ�¼    ]  : 
 *
 *	[ ��  �� ]     [�汾]         [�޸���]         [�޸�����] 
 *	2019/03/19     1.0                  ���ı�                     ����
 *	----------------------------------------------------------------------------
 *	
 *	[ ����˵��    ]  :
 *
 *	[## private IniFunc() {} ]:
 *		����: ���캯��
 *
 *	[## public static String getIniKey (String k) {} ]:
 *		����: ���INI�ļ��е�ָ�����ļ�ֵ
 *
 *	[## public static void setIniKey (String k, String v) {} ]:
 *		����: ����k���ļ�ֵΪv����
 *
 *	[## public static void saveIni (String k[]) {} ]:
 *		����: ��k�ַ����������м�����Ӧ�ļ�ֵ���浽INI�ļ���
 *	
 *  [ ��������    ]  : setIniKey ()�������ܴ����ֵ�е�ת���ַ�
 *
 *##############################################################################
 */

package system;

import java.util.*;
import java.io.*;


public class IniFunc {
	
	private static Properties ini = null;
	
	static {
		try	{
			ini = new Properties ();
			ini.load (new FileInputStream ("lib/config.ini"));
		}catch (Exception ex) {
			System.out.println ("Load CONFIG.INI is false!!");
		}
	}
	
	/**=======================================================================**
	 *		[## private sunini() {} ]:		���캯��
	 *			����   ����
	 *			����ֵ ����
	 *			���η� ��private
	 *			����   ����ֹʵ����sunini����
	 **=======================================================================**
	 */
	private IniFunc() {
	}
	
	/**=======================================================================**
	 *		[## public static String getIniKey (String k) {} ]:	
	 *			����   ��String�����ʾ��
	 *			����ֵ ��String�����ʾk������Ӧ�ļ�ֵ�����ʧ���򷵻ؿմ�
	 *			���η� ��public static ���Բ�ʵ���������ֱ�ӵ��÷���
	 *			����   �����INI�ļ��е�ָ�����ļ�ֵ
	 **=======================================================================**
	 */
	public static String getIniKey (String k) {
		if(!ini.containsKey (k)) {		//�Ƿ��� k �����
			System.out.println ("The [ " + k + " ] Key is not exist!!");
			return "";
		}
		return ini.get(k).toString ();
	}
	
	/**=======================================================================**
	 *		[## public static void setIniKey (String k, String v) {} ]:	
	 *			����   ��String k�����ʾ��,String v�����ʾ��ֵ
	 *			����ֵ ����
	 *			���η� ��public static ���Բ�ʵ���������ֱ�ӵ��÷���
	 *			����   ������k���ļ�ֵΪv����
	 **=======================================================================**
	 */
	public static void setIniKey (String k, String v) {
		if(!ini.containsKey (k)) {		//�Ƿ��� k �����
			System.out.println ("The [ " + k + " ] Key is not exist!!");
			return;
		}
		ini.put (k, v);
	}
	
	/**=======================================================================**
	 *		[## public static void saveIni (String k[]) {} ]:	
	 *			����   ��String k[]�ַ��������ʾҪ��������м�
	 *			����ֵ ����
	 *			���η� ��public static ���Բ�ʵ���������ֱ�ӵ��÷���
	 *			����   ����k�ַ����������м�����Ӧ�ļ�ֵ���浽INI�ļ���
	 **=======================================================================**
	 */
	public static void saveIni (String k[]) {
		try	{
			FileWriter fw = new FileWriter ("config.ini");
			BufferedWriter bw = new BufferedWriter ( fw );
			//ѭ������i��k�ַ���������±�
			for (int i = 0; i < k.length; i++) {
				bw.write (k[i] + "=" + getIniKey (k[i]));
				bw.newLine ();
			}
			bw.close ();
			fw.close ();
		}catch (Exception ex) {
			System.out.println ("Save CONFIG.INI is false.");
		}
	}
	
}