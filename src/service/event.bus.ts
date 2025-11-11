import { Observable, Subject } from 'rxjs';

export enum EventType {
  EVENT_NONE,
  EVENT_REDIRECT,
  EVENT_MESSAGE_ERROR,
  EVENT_MESSAGE_SUCCESS,
  EVENT_DEVICE_FOUND,
  EVENT_DEVICE_LOSS,
}

export interface EventData {
  type: EventType;
  data: unknown;
}

class EventBusSubject {
  private bus = new Subject<any>();

  getData(): Observable<any> {
    return this.bus.asObservable();
  }

  sendData(data: EventData = { type: EventType.EVENT_NONE, data: {} }): void {
    this.bus.next(data);
  }
}

const eventBus = new EventBusSubject();
export default eventBus;
