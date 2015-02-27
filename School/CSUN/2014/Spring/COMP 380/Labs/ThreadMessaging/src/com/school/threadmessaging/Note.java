package com.school.threadmessaging;

import android.os.Handler;
import android.os.Parcel;
import android.os.Parcelable;

public class Note implements Parcelable
{	
	String		from,
				to,
				message;
	double[]	data	=	new	double[3];
	
	private Note(Parcel in)
	{
		this.from		=	in.readString();
		this.to			=	in.readString();
		this.message	=	in.readString();
		this.data[0]	=	in.readDouble();
		this.data[1]	=	in.readDouble();
		this.data[2]	=	in.readDouble();
	}
	
	public Note(String from, String to, String msg)
	{
		this.from		=	from;
		this.to			=	to;
		this.message	=	msg;
		this.data[0]	=	0.0;
		this.data[1]	=	0.0;
		this.data[2]	=	0.0;
	}
	
	public Note(String from, String to, String msg, double[] data)
	{
		this.from		=	from;
		this.to			=	to;
		this.message	=	msg;
		this.data		=	data;
	}
	
	@Override public int describeContents()
	{
		return 0;
	}

	@Override public void writeToParcel(Parcel dest, int flags)
	{
		dest.writeString(from);
		dest.writeString(to);
		dest.writeString(message);
		dest.writeDouble(data[0]);
		dest.writeDouble(data[1]);
		dest.writeDouble(data[2]);
	}
	
	public static final Parcelable.Creator<Note> CREATOR	= new Parcelable.Creator<Note>()
	{
		public Note createFromParcel(Parcel in)
		{
			return new Note(in);
		}

		public Note[] newArray(int size)
		{
			return new Note[size];
		}
	};
}