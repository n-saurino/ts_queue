#pragma once
#include <iostream>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <optional>

template<typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue(/* args */){
        
    }

    ~ThreadSafeQueue(){

    }

    std::optional<T> Pop(){
        std::unique_lock<std::mutex> ul{mtx_};
        cv_.wait(ul, [this](){return stop_flag_ || !q_.empty();});
        
        if(stop_flag_ && q_.empty()){
            return std::nullopt;
        }
        
        T val{q_.front()};
        q_.pop_front();
        return val;
    }
    
    bool Push(const T& val){
        {
            std::unique_lock<std::mutex> ul{mtx_};
            q_.push_back(val);
        }
        cv_.notify_one();
        return true;
    }
    
    void Stop(){
        {
            std::unique_lock<std::mutex> ul(mtx_);
            stop_flag_ = true;
        }
        cv_.notify_all();
    }
    
    int Size(){
        std::unique_lock<std::mutex> ul(mtx_);
        return q_.size();
    }
    
    bool Empty(){
        std::unique_lock<std::mutex> ul(mtx_);
        return q_.size() == 0;
    }

private:
    std::deque<T> q_{};
    std::mutex mtx_{};
    std::condition_variable cv_{};
    bool stop_flag_{};
};


