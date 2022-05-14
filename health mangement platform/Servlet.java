import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;












import Bean.User_bean;

import java.sql.*;

public class Servlet {
	private static final long serialVersionUID = 1L;
    
	static String subject="";
	static String id="";
    /**
     * @see HttpServlet#HttpServlet()
     */
    public Servlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doPost(request,response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		 String meth=request.getParameter("method");
		 if("login".equals(meth))
		 {
			 String id = request.getParameter("id");
			 String password = request.getParameter("password");
			 String subject=request.getParameter("subject");
			 User_bean userBean = new User_bean(subject);
			 boolean isValid=userBean.valid(id,password);
			 if(isValid){
				  System.out.println("��¼�ɹ���");
				  request.setAttribute("id", id);
				  if(subject.equals("student"))
				  {request.getRequestDispatcher("student_welcome.jsp").forward(request, response);
				  return;}
				  if(subject.equals("teacher"))
				  {request.getRequestDispatcher("techaer_welcome.jsp").forward(request, response);
				  return;}
			  }else{
				  System.out.println("�û�����������󣬵�¼ʧ�ܣ�");
				  response.sendRedirect("login.jsp");
				  return;
			  }
			 
		 }
		    if("logout".equals(meth)){
		           System.out.println("�˳��ɹ�");
		           response.sendRedirect("login.jsp");
		           return;
			  }
		    if("register_student".equals(meth)){
		    	
		    	String id=request.getParameter("id");
				String password=request.getParameter("password");
				String refill=request.getParameter("refill");
				User_bean us1=new User_bean("student");
				if(id==null||password==null||refill==null){
				System.out.println("�û����������벻��Ϊ��");
				response.sendRedirect("register_failure.jsp");
				return;
				}
				String tmp = password.replaceAll("\\p{P}", "");
				 if (password.length() != tmp.length()||password.length()<6||password.length()>8)
				 {System.out.println("���벻���ϱ�׼");
				 response.sendRedirect("register_failure.jsp"); return;}
				 if(!password.equals(refill)){System.out.println("����ǰ��һ��");
				 response.sendRedirect("register_failure.jsp");return;}
				User_bean us=new User_bean("student");
				 boolean b=us.isExist(id);
				if(!b){
		            us.add(id, password);
					System.out.println("ע��ɹ�"+":id="+id);
					us1.add(id,password);
				     response.sendRedirect("register_success.jsp");
				     return;
				}
				else{
					System.out.println("�û����Ѿ�����");
					response.sendRedirect("register_failure.jsp");
					return;
		    }
	}
		    if("register_admin".equals(meth)){
		    	
		    	String id=request.getParameter("id");
				String password=request.getParameter("password");
				String refill=request.getParameter("refill");
				User_bean us1=new User_bean("admin");
				if(id==null||password==null||refill==null){
				System.out.println("�û����������벻��Ϊ��");
				response.sendRedirect("register_failure.jsp");
				return;
				}
				String tmp = password.replaceAll("\\p{P}", "");
				 if (password.length() != tmp.length()||password.length()<6||password.length()>8)
				 {System.out.println("���벻���ϱ�׼");
				 response.sendRedirect("register_failure.jsp"); return;}
				 if(!password.equals(refill)){System.out.println("����ǰ��һ��");
				 response.sendRedirect("register_failure.jsp");return;}
				User_bean us=new User_bean("student");
				 boolean b=us.isExist(id);
				if(!b){
		            us.add(id, password);
					System.out.println("ע��ɹ�"+":id="+id);
					us1.add(id,password);
				     response.sendRedirect("register_success.jsp");
				     return;
				}
				else{
					System.out.println("�û����Ѿ�����");
					response.sendRedirect("register_failure.jsp");
					return;
		    }
	}		    if("register_teacher".equals(meth)){
    	
    	String id=request.getParameter("id");
		String password=request.getParameter("password");
		String refill=request.getParameter("refill");
		User_bean us1=new User_bean("teacher");
		if(id==null||password==null||refill==null){
		System.out.println("�û����������벻��Ϊ��");
		response.sendRedirect("register_failure.jsp");
		return;
		}
		String tmp = password.replaceAll("\\p{P}", "");
		 if (password.length() != tmp.length()||password.length()<6||password.length()>8)
		 {System.out.println("���벻���ϱ�׼");
		 response.sendRedirect("register_failure.jsp"); return;}
		 if(!password.equals(refill)){System.out.println("����ǰ��һ��");
		 response.sendRedirect("register_failure.jsp");return;}
		User_bean us=new User_bean("student");
		 boolean b=us.isExist(id);
		if(!b){
            us.add(id, password);
			System.out.println("ע��ɹ�"+":id="+id);
			us1.add(id,password);
		     response.sendRedirect("register_success.jsp");
		     return;
		}
		else{
			System.out.println("�û����Ѿ�����");
			response.sendRedirect("register_failure.jsp");
			return;
    }
}
	if("studentModify".equals(meth))
	{
		
		String updatePassword=request.getParameter("updatePassword");
		String tmp = updatePassword.replaceAll("\\p{P}", "");
		 if (updatePassword.length() != tmp.length()||updatePassword.length()<6||updatePassword.length()>8)
		 {System.out.println("���벻���ϱ�׼");response.sendRedirect("student_welcome.jsp");return;}
		User_bean us=new User_bean(subject);
		String sql="update user_schema.student set password='"+updatePassword+"' where id='"+id+"'";
		us.db.update(sql);
		response.sendRedirect("student_welcome.jsp");return;
	}
		
	if("loginJSF".equals(meth))
	{
		subject=request.getParameter("subject");
		String id=request.getParameter("id");
		String password=request.getParameter("password");
		User_bean us=new User_bean(subject);
		boolean bo= us.valid(id, password);
		
		if(bo==true){
			System.out.println("��¼�ɹ�");
			if(subject.equals("student")){response.sendRedirect("student_welcome.jsp");return;}
			if(subject.equals("teacher")){response.sendRedirect("teacher_welcome.jsp");return;}
		}
		System.out.println("��¼ʧ��");return;
	}
	if("teacherModify".equals(meth))
	{
		
		String updatePassword=request.getParameter("updatePassword");
		String tmp = updatePassword.replaceAll("\\p{P}", "");
		 if (updatePassword.length() != tmp.length()||updatePassword.length()<6||updatePassword.length()>8)
		 {System.out.println("���벻���ϱ�׼");response.sendRedirect("student_welcome.jsp");return;}
		User_bean us=new User_bean(subject);
		String sql="update user_schema.student set password='"+updatePassword+"' where id='"+id+"'";
		us.db.update(sql);
		response.sendRedirect("teacher_welcome.jsp");return;
	}
	if("registPaper".equals(meth))
	{
		String s1=request.getParameter("s1");
		String s2=request.getParameter("s2");
		String s3=request.getParameter("s3");
		String t1=request.getParameter("t1");
		String t2=request.getParameter("t2");
		String t3=request.getParameter("t3");
		String j1=request.getParameter("j1");
		String j2=request.getParameter("j2");
		String j3=request.getParameter("j3");
		User_bean us=new User_bean(subject);
		String sql="select * from  user_schema.questions where id='"+s1+"'";//ѡ�����һ���ǿ��Է��� ���ڶ�������Ŀid������������Ŀ�����������Ǵ�
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questions where id='"+s2+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questions where id='"+s3+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questionj where id='"+j1+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questionj where id='"+j2+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questionj where id='"+j3+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questiont where id='"+t1+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questiont where id='"+t2+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		sql="select * from  user_schema.questiont where id='"+t3+"'";
		us.db.query(sql);
		if(!us.db.next()){return ;}
		int i;
		for(i=1;;i++)
		{sql="select * from  user_schema.paper where id='"+i+"'";
		us.db.query(sql);
		if(us.db.next()){break;}
		}
		sql="insert into user_shcema.paper1 s1='"+s1+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 s2='"+s2+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 s3='"+s3+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 t1='"+t1+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 t2='"+t2+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 t3='"+t3+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 j1='"+j1+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 j2='"+j2+"' where id='"+i+"'";
		us.db.update(sql);
		sql="insert into user_shcema.paper1 j3='"+j3+"' where id='"+i+"'";
		us.db.update(sql);
		response.sendRedirect("teacher_welcome.jsp");return;
	}
	if("teacherModify".equals(meth))
	{
		
		String updatePassword=request.getParameter("updatePassword");
		String tmp = updatePassword.replaceAll("\\p{P}", "");
		 if (updatePassword.length() != tmp.length()||updatePassword.length()<6||updatePassword.length()>8)
		 {System.out.println("���벻���ϱ�׼");response.sendRedirect("student_welcome.jsp");return;}
		User_bean us=new User_bean(subject);
		String sql="update user_schema.student set password='"+updatePassword+"' where id='"+id+"'";
		us.db.update(sql);
		response.sendRedirect("teacher_welcome.jsp");return;
	}
	if("chooseTest".equals(meth))
	{
		String testSub=request.getParameter("testSub");
		User_bean us=new User_bean(subject);
		String sql="select * from  user_schema."+subject+"where id='"+id+"'and "+testSub+"='1'";//ѧ���������ѧ���У�ÿ����Ĭ��Ϊ0��ע����Ϊ1
		us.db.query(sql);
		if(us.db.next())
		{response.sendRedirect("testPage.jsp");return;}
		System.out.println("ѡ��ʧ�ܣ�û�н���ע�ῼ��");
		response.sendRedirect("student_welcome.jsp");return;
	}
	if("testPage".equals(meth))
	{
		String s1ta=request.getParameter("s1ta");
		String s2ta=request.getParameter("s2ta");
		String s3ta=request.getParameter("s3ta");
		String t1ta=request.getParameter("t1ta");
		String t2ta=request.getParameter("t2ta");
		String t3ta=request.getParameter("t3ta");
		String j1ta=request.getParameter("j1ta");
		String j2ta=request.getParameter("j2ta");
		String j3ta=request.getParameter("j3ta");
		int passivegrade=0;
		int activegrade=0;//�ύ�Ծ�ʱ��ճɼ�
		User_bean us=new User_bean(subject);
		String sql="select * from  user_schema.questions where id='"+s1+"'";
		us.db.query(sql);
		if(s1ta.equals(us.db.getRs().getString(3))){passivegrade=passivegrade+3;}
		sql="select * from  user_schema.questions where id='"+s2+"'";
		if(s2ta.equals(us.db.getRs().getString(3))){passivegrade=passivegrade+3;}
		sql="select * from  user_schema.questions where id='"+s3+"'";
		if(s3ta.equals(us.db.getRs().getString(3))){passivegrade=passivegrade+4;}
		sql="insert into user_schema.paper values('"+id+"','"+testSub+"','"+s1t+"','"+s2t+"','"+s3t+"','"+t1t+"','"+t2t+"','"+t3t+"','"+j1t+"','"+j2t+"','"+j3t+"','"+s1ta+"','"+s2ta+"','"+s3ta+"','"+t1ta+"','"+t2ta+"','"+t3ta+"','"+j1ta+"','"+j2ta+"','"+j3ta+"','"+passivegrade+"','"+activegrade+"')";
		//paper���� ��һ�� ����id ���ڶ��п��Կ�Ŀ,��9�п�����Ŀ,�ٺ�9�п��Դ�,�ٺ�һ�п͹�����������һ�����������
		return "success";
	}
	}
}

