package data;

public class Page {
	private int pageIndex=1;
	private int pageSize=5;
	private int count;
	private int totalpage;
	
	public int getPageIndex() {
		return pageIndex;
	}
	
	public void setPageIndex(int pageIndex) {
		this.pageIndex = pageIndex;
	}
	
	public int getPageSize() {
		return pageSize;
	}
	
	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}
	
	public int getCount() {
		return count;
	}
	
	public void setCount(int count) {
		this.count = count;
	}
	
	public int getTotalpage() {
		return totalpage;
	}
	
	public void setTotalpage(int totalpage) {
		this.totalpage = totalpage;
	}

	public Page(int pageIndex, int pageSize, int count, int totalpage) {
		super();
		this.pageIndex = pageIndex;
		this.pageSize = pageSize;
		this.count = count;
		this.totalpage = totalpage;
	}

	public Page() {
		// TODO 自动生成的构造函数存根
	}
}
