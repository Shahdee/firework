/*
 *  TimeMachine.h
 *  Engine
 *
 *  Created by vasiliym on 02.12.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TIMEMACHINE_H_
#define _TIMEMACHINE_H_

#include "Core/MessageManager.h"

namespace Core {
	
	/// Класс для отложенного выполнения некоторых действий
	class TimeMachine {
	private:
		enum {
			UNKNOWN_TYPE = 0, COMMAND_TYPE, MESSAGE_TYPE, CALLBACK_TYPE
		};
		typedef struct Job {
			std::string command;
			Message message;
			Callback func;
			void* userData;
			int type;
			float time;
			Job();
			Job(std::string c, int msec);
			Job(Message m, int msec);
			Job(Callback func, void* userData, int msec);
			void doJob();
		} Job;
		
		typedef std::map<int, Job> JobMap;
		JobMap jobs;
		std::vector<int> finished;
		int nextId;
	public:
		TimeMachine();
		~TimeMachine();
		
		/// Выполнить lua строку через заданное кол-во миллисекунд
		/// Возвращает уникальный идентификатор задания
		int doString(std::string command, int msec);
		/// Отправить сообщение через заданное кол-во миллисекунд
		/// Возвращает уникальный идентификатор задания
		int doMessage(Message message, int msec);
		/// Вызвать заданную функцию через заданное кол-во миллисекунд
		/// Возвращает уникальный идентификатор задания
		int doCallback(Callback func, void* userData, int msec);
		/// Отменить выполнение указанного задания
		/// Возвращает 0 если задание отменено, -1 если такого задания нет, 1 если задание уже было выполнено
		int cancelJob(int job);
		/// Возвращает 0 если задание есть в очереди, -1 если такого задания нет, 1 если задание уже было выполнено
		int getState(int job);
		/// 
		void Update(float dt);
		/// 
		void Clear();
		
		static TimeMachine& GetInstance();
	};
}

#endif // _TIMEMACHINE_H_