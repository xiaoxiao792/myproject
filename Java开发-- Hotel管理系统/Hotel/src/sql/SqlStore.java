package sql;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class SqlStore {

	public class SqlQueue {
	    // 数据库队列
	    BlockingQueue<String> queue = new LinkedBlockingQueue<String>(5);
	
	    // 生产数据库语句
	    public void produce(String sql) throws InterruptedException {
	        // put方法放入一个数据库语句，已满等待
	    	queue.put(sql);
	    }
	
	    // 消费数据库语句
	    public String consume() throws InterruptedException {
	        // take方法取出一个数据库语句，若queue为空，则等待
	        return queue.take();
	    }
	}

	// 定义数据库生产者
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
	            // 生产数据库语句
	            System.out.println("生产者准备生产数据库语句：" + instance);
	            sqlqueue.produce(sql);
	            System.out.println("!生产者生产数据库语句完毕：" + instance);
	            // 休眠300ms
	           // Thread.sleep(300);
	        } catch (InterruptedException ex) {
	            System.out.println("Producer Interrupted");
	        }
	    }
	}

	// 定义数据库语句消费者
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
                // 消费数据库语句
                System.out.println("消费者准备消费数据库语句：" + instance);
                String str = sqlqueue.consume();
                System.out.println(str);
                SqlFunc.updata(str);
                System.out.println("!消费者消费数据库语句完毕：" + instance);
                // 休眠1000ms
               // Thread.sleep(1000);
            }
        } catch (InterruptedException ex) {
            System.out.println("Consumer Interrupted");
        }
    }

}

}
