package sql;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class SqlStore {

	public class SqlQueue {
	    // ���ݿ����
	    BlockingQueue<String> queue = new LinkedBlockingQueue<String>(5);
	
	    // �������ݿ����
	    public void produce(String sql) throws InterruptedException {
	        // put��������һ�����ݿ���䣬�����ȴ�
	    	queue.put(sql);
	    }
	
	    // �������ݿ����
	    public String consume() throws InterruptedException {
	        // take����ȡ��һ�����ݿ���䣬��queueΪ�գ���ȴ�
	        return queue.take();
	    }
	}

	// �������ݿ�������
	public class Producer{
	    private String instance;
	    private SqlQueue sqlqueue;
	    private String sql;
	
	    public Producer(String instance, SqlQueue sqlqueue) {
	        this.instance = instance;
	        this.sqlqueue = sqlqueue;
	    }
	    
	    public void addsql(String sql) {
	    	this.sql = sql;
	    	run();
	    }
	
	    public void run() {
	        try {      
	            // �������ݿ����
	            System.out.println("������׼���������ݿ���䣺" + instance);
	            sqlqueue.produce(sql);
	            System.out.println("!�������������ݿ������ϣ�" + instance);
	            // ����300ms
	           // Thread.sleep(300);
	        } catch (InterruptedException ex) {
	            System.out.println("Producer Interrupted");
	        }
	    }
	}

	// �������ݿ����������
	public class Consumer implements Runnable {
	    private String instance;
	    private SqlQueue sqlqueue;
	
	    public Consumer(String instance, SqlQueue sqlqueue) {
	        this.instance = instance;
	        this.sqlqueue = sqlqueue;
    }

    public void run() {
        try {
            while (true) {
                // �������ݿ����
                System.out.println("������׼���������ݿ���䣺" + instance);
                String str = sqlqueue.consume();
                System.out.println(str);
                SqlFunc.updata(str);
                System.out.println("!�������������ݿ������ϣ�" + instance);
                // ����1000ms
               // Thread.sleep(1000);
            }
        } catch (InterruptedException ex) {
            System.out.println("Consumer Interrupted");
        }
    }

}

}
