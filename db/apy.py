from typing import Any, Dict, List, Optional, Union
from flask import Flask, render_template, request, jsonify
import pymysql
from datetime import datetime

app = Flask(__name__)

# ============ 数据库配置 ============
DB_CONFIG: Dict[str, Any] = {
    'host': 'localhost',
    'user': 'root',
    'password': '2746217203',
    'database': 'order_book',
    'charset': 'utf8mb4',
    'cursorclass': pymysql.cursors.DictCursor
}


def get_db_connection() -> "pymysql.connections.Connection":
    """获取MySQL数据库连接"""
    return pymysql.connect(**DB_CONFIG)



# ============ 日期格式化辅助函数 ============
def format_date_str(date_str_or_obj: Optional[Union[str, datetime]]) -> str:
    """将日期字符串或对象格式化为 YYYY-MM-DD 格式"""
    if not date_str_or_obj:
        return ""

    try:
        # 如果是字符串，尝试多种格式解析
        if isinstance(date_str_or_obj, str):
            for fmt in [
                '%Y-%m-%d',
                '%Y-%m-%d %H:%M:%S',
                '%Y-%m-%d %H:%M:%S.%f',
                '%Y/%m/%d',
                '%Y/%m/%d %H:%M:%S',
                '%d/%m/%Y',
                '%Y.%m.%d',
            ]:
                try:
                    dt = datetime.strptime(date_str_or_obj, fmt)
                    return dt.strftime('%Y-%m-%d')
                except ValueError:
                    continue
            # 如果都无法解析，尝试截取前10个字符
            if len(date_str_or_obj) >= 10:
                return date_str_or_obj[:10]
            return date_str_or_obj

        # 如果是 datetime/date 对象
        elif isinstance(date_str_or_obj, datetime):
            return date_str_or_obj.strftime('%Y-%m-%d')

        else:
            return str(date_str_or_obj)

    except Exception as e:
        print(f"日期格式化错误: {e}, 原始值: {date_str_or_obj}")
        return str(date_str_or_obj)


# ============ 首页路由 ============
@app.route('/')
def index():
    return render_template('index.html')


# ============ 教材管理API ============
@app.route('/api/textbooks', methods=['GET'])
def get_textbooks():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM textbooks')
            textbooks: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(textbooks)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/textbooks', methods=['POST'])
def add_textbook():
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                INSERT INTO textbooks (isbn, title, author, publisher, edition, price, stock_quantity)
                VALUES (%s, %s, %s, %s, %s, %s, %s)
            ''', (
                data.get('isbn'), data.get('title'), data.get('author', ''),
                data.get('publisher', ''), data.get('edition', ''),
                data.get('price', 0), data.get('stock_quantity', 0)
            ))
            conn.commit()
            textbook_id: int = cursor.lastrowid  # type: ignore
            return jsonify({'message': '教材添加成功', 'id': textbook_id})
    except pymysql.IntegrityError:
        return jsonify({'error': 'ISBN已存在'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/textbooks/<int:textbook_id>', methods=['PUT'])
def update_textbook(textbook_id: int):
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                UPDATE textbooks 
                SET isbn=%s, title=%s, author=%s, publisher=%s, edition=%s, price=%s, stock_quantity=%s
                WHERE id=%s
            ''', (
                data.get('isbn'), data.get('title'), data.get('author', ''),
                data.get('publisher', ''), data.get('edition', ''),
                data.get('price', 0), data.get('stock_quantity', 0), textbook_id
            ))
            conn.commit()
            return jsonify({'message': '教材更新成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/textbooks/<int:textbook_id>', methods=['DELETE'])
def delete_textbook(textbook_id: int):
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('DELETE FROM textbooks WHERE id = %s', (textbook_id,))
            conn.commit()
            return jsonify({'message': '教材删除成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 学生管理API ============
@app.route('/api/students', methods=['GET'])
def get_students():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM students')
            students: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(students)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/students', methods=['POST'])
def add_student():
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                INSERT INTO students (student_id, name, class_name, contact_phone, email)
                VALUES (%s, %s, %s, %s, %s)
            ''', (
                data.get('student_id'), data.get('name'), data.get('class_name'),
                data.get('contact_phone', ''), data.get('email', '')
            ))
            conn.commit()
            student_row_id: int = cursor.lastrowid  # type: ignore
            return jsonify({'message': '学生添加成功', 'id': student_row_id})
    except pymysql.IntegrityError:
        return jsonify({'error': '学号已存在'}), 400
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/students/<int:student_id>', methods=['PUT'])
def update_student(student_id: int):
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                UPDATE students 
                SET student_id=%s, name=%s, class_name=%s, contact_phone=%s, email=%s
                WHERE id=%s
            ''', (
                data.get('student_id'), data.get('name'), data.get('class_name'),
                data.get('contact_phone', ''), data.get('email', ''), student_id
            ))
            conn.commit()
            return jsonify({'message': '学生更新成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/students/<int:student_id>', methods=['DELETE'])
def delete_student(student_id: int):
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            # 检查是否有相关订单
            cursor.execute('SELECT * FROM orders WHERE student_id = %s', (student_id,))
            orders: List[Dict[str, Any]] = cursor.fetchall() or []
            if orders:
                return jsonify({'error': '该学生有相关订单，无法删除'}), 400

            cursor.execute('DELETE FROM students WHERE id = %s', (student_id,))
            conn.commit()
            return jsonify({'message': '学生删除成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 订单管理API ============
@app.route('/api/orders', methods=['GET'])
def get_orders():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                SELECT o.*, s.name as student_name, s.student_id, s.class_name,
                       t.title as textbook_title, t.price
                FROM orders o
                JOIN students s ON o.student_id = s.id
                JOIN textbooks t ON o.textbook_id = t.id
                ORDER BY o.order_date DESC
            ''')
            orders: List[Dict[str, Any]] = cursor.fetchall() or []

            # 格式化日期字段为 YYYY-MM-DD
            for order in orders:
                if 'order_date' in order and order['order_date'] is not None:
                    order['order_date'] = format_date_str(order['order_date'])

        return jsonify(orders)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/orders/<int:order_id>', methods=['GET'])
def get_order(order_id: int):
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                SELECT o.*, s.name as student_name, s.student_id, s.class_name,
                       t.title as textbook_title, t.price
                FROM orders o
                JOIN students s ON o.student_id = s.id
                JOIN textbooks t ON o.textbook_id = t.id
                WHERE o.id = %s
            ''', (order_id,))
            order: Optional[Dict[str, Any]] = cursor.fetchone()
            if order:
                if 'order_date' in order and order['order_date'] is not None:
                    order['order_date'] = format_date_str(order['order_date'])
                return jsonify(order)
            else:
                return jsonify({'error': '订单不存在'}), 404
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/orders', methods=['POST'])
def add_order():
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            # 获取教材价格
            cursor.execute('SELECT price FROM textbooks WHERE id = %s', (data.get('textbook_id'),))
            textbook: Optional[Dict[str, Any]] = cursor.fetchone()
            if not textbook or 'price' not in textbook:
                return jsonify({'error': '教材不存在'}), 400

            try:
                price_value = float(textbook.get('price', 0))
            except Exception:
                price_value = 0.0

            order_quantity = int(data.get('order_quantity', 0))
            total_amount = price_value * order_quantity

            # 处理日期
            order_date = data.get('order_date')
            if not order_date:
                order_date = datetime.now().strftime('%Y-%m-%d')
            else:
                try:
                    if 'T' in order_date:
                        order_date = order_date.split('T')[0]
                    elif ' ' in order_date:
                        order_date = order_date.split(' ')[0]
                    datetime.strptime(order_date, '%Y-%m-%d')
                except ValueError:
                    return jsonify({'error': '日期格式不正确，请使用YYYY-MM-DD格式'}), 400

            cursor.execute('''
                INSERT INTO orders (student_id, textbook_id, order_quantity, order_date, total_amount, status)
                VALUES (%s, %s, %s, %s, %s, %s)
            ''', (
                data.get('student_id'), data.get('textbook_id'), order_quantity,
                order_date,
                total_amount, 'pending'
            ))

            conn.commit()
            order_id: int = cursor.lastrowid  # type: ignore
            return jsonify({'message': '订购成功', 'id': order_id})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/orders/<int:order_id>/status', methods=['PUT'])
def update_order_status(order_id: int):
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('UPDATE orders SET status = %s WHERE id = %s', (data.get('status'), order_id))
            conn.commit()
            return jsonify({'message': '订单状态更新成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/orders/<int:order_id>', methods=['DELETE'])
def delete_order(order_id: int):
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM payments WHERE order_id = %s', (order_id,))
            payment: Optional[Dict[str, Any]] = cursor.fetchone()

            cursor.execute('SELECT * FROM distributions WHERE order_id = %s', (order_id,))
            distribution: Optional[Dict[str, Any]] = cursor.fetchone()

            if payment or distribution:
                return jsonify({'error': '该订单已有收费或发放记录，无法删除'}), 400

            cursor.execute('DELETE FROM orders WHERE id = %s', (order_id,))
            conn.commit()
            return jsonify({'message': '订单删除成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 收费管理API ============
@app.route('/api/payments', methods=['GET'])
def get_payments():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                SELECT p.*, o.id as order_id, s.name as student_name, s.student_id, s.class_name,
                       t.title as textbook_title
                FROM payments p
                JOIN orders o ON p.order_id = o.id
                JOIN students s ON o.student_id = s.id
                JOIN textbooks t ON o.textbook_id = t.id
                ORDER BY p.payment_date DESC
            ''')
            payments: List[Dict[str, Any]] = cursor.fetchall() or []
            for payment in payments:
                if 'payment_date' in payment and payment['payment_date'] is not None:
                    payment['payment_date'] = format_date_str(payment['payment_date'])
        return jsonify(payments)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/payments', methods=['POST'])
def add_payment():
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM orders WHERE id = %s', (data.get('order_id'),))
            order: Optional[Dict[str, Any]] = cursor.fetchone()
            if not order:
                return jsonify({'error': '订单不存在'}), 400

            payment_date = data.get('payment_date')
            if not payment_date:
                payment_date = datetime.now().strftime('%Y-%m-%d')
            else:
                try:
                    if 'T' in payment_date:
                        payment_date = payment_date.split('T')[0]
                    elif ' ' in payment_date:
                        payment_date = payment_date.split(' ')[0]
                    datetime.strptime(payment_date, '%Y-%m-%d')
                except ValueError:
                    return jsonify({'error': '日期格式不正确，请使用YYYY-MM-DD格式'}), 400

            receipt_number = f"REC{datetime.now().strftime('%Y%m%d%H%M%S')}"

            cursor.execute('''
                INSERT INTO payments (order_id, payment_amount, payment_date, payment_method, receipt_number)
                VALUES (%s, %s, %s, %s, %s)
            ''', (
                data.get('order_id'), data.get('payment_amount', 0), payment_date,
                data.get('payment_method', ''), receipt_number
            ))

            cursor.execute('UPDATE orders SET status = %s WHERE id = %s', ('paid', data.get('order_id')))
            conn.commit()
            return jsonify({'message': '收费记录添加成功', 'receipt_number': receipt_number})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/payments/<int:payment_id>', methods=['DELETE'])
def delete_payment(payment_id: int):
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM payments WHERE id = %s', (payment_id,))
            payment: Optional[Dict[str, Any]] = cursor.fetchone()
            if not payment:
                return jsonify({'error': '收费记录不存在'}), 404

            order_id = payment.get('order_id')
            cursor.execute('DELETE FROM payments WHERE id = %s', (payment_id,))
            if order_id:
                cursor.execute('UPDATE orders SET status = %s WHERE id = %s', ('confirmed', order_id))

            conn.commit()
            return jsonify({'message': '收费记录删除成功，订单状态已重置'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 发放管理API ============
@app.route('/api/distributions', methods=['GET'])
def get_distributions():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('''
                SELECT d.*, o.id as order_id, s.name as student_name, s.student_id, s.class_name,
                       t.title as textbook_title
                FROM distributions d
                JOIN orders o ON d.order_id = o.id
                JOIN students s ON o.student_id = s.id
                JOIN textbooks t ON o.textbook_id = t.id
                ORDER BY d.distribute_date DESC
            ''')
            distributions: List[Dict[str, Any]] = cursor.fetchall() or []
            for distribution in distributions:
                if 'distribute_date' in distribution and distribution['distribute_date'] is not None:
                    distribution['distribute_date'] = format_date_str(distribution['distribute_date'])
        return jsonify(distributions)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/distributions', methods=['POST'])
def add_distribution():
    data: Dict[str, Any] = request.json or {}
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM orders WHERE id = %s', (data.get('order_id'),))
            order: Optional[Dict[str, Any]] = cursor.fetchone()
            if not order:
                return jsonify({'error': '订单不存在'}), 400

            cursor.execute('SELECT stock_quantity FROM textbooks WHERE id = %s', (order.get('textbook_id'),))
            textbook: Optional[Dict[str, Any]] = cursor.fetchone()
            if not textbook:
                return jsonify({'error': '教材不存在'}), 400

            available: int = int(textbook.get('stock_quantity', 0))
            distribute_quantity = int(data.get('distribute_quantity', 0))
            if available < distribute_quantity:
                return jsonify({'error': '库存不足'}), 400

            distribute_date = data.get('distribute_date')
            if not distribute_date:
                distribute_date = datetime.now().strftime('%Y-%m-%d')
            else:
                try:
                    if 'T' in distribute_date:
                        distribute_date = distribute_date.split('T')[0]
                    elif ' ' in distribute_date:
                        distribute_date = distribute_date.split(' ')[0]
                    datetime.strptime(distribute_date, '%Y-%m-%d')
                except ValueError:
                    return jsonify({'error': '日期格式不正确，请使用YYYY-MM-DD格式'}), 400

            cursor.execute('''
                INSERT INTO distributions (order_id, distribute_date, distribute_quantity, distributor, receive_signature)
                VALUES (%s, %s, %s, %s, %s)
            ''', (
                data.get('order_id'), distribute_date, distribute_quantity,
                data.get('distributor', ''), data.get('receive_signature', '')
            ))

            cursor.execute('''
                UPDATE textbooks 
                SET stock_quantity = stock_quantity - %s 
                WHERE id = %s
            ''', (distribute_quantity, order.get('textbook_id')))

            cursor.execute('UPDATE orders SET status = %s WHERE id = %s', ('distributed', data.get('order_id')))
            conn.commit()
            return jsonify({'message': '发放记录添加成功'})
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 统计查询API ============
@app.route('/api/statistics/orders', methods=['GET'])
def get_order_statistics():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM order_statistics ORDER BY order_date DESC')
            statistics: List[Dict[str, Any]] = cursor.fetchall() or []
            for stat in statistics:
                if 'order_date' in stat and stat['order_date'] is not None:
                    stat['order_date'] = format_date_str(stat['order_date'])
        return jsonify(statistics)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/statistics/class-summary', methods=['GET'])
def get_class_summary():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM class_order_summary')
            summary: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(summary)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/statistics/textbook-summary', methods=['GET'])
def get_textbook_summary():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM textbook_order_summary')
            summary: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(summary)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/statistics/financial', methods=['GET'])
def get_financial_statistics():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM financial_summary')
            statistics: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(statistics)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/alerts/inventory', methods=['GET'])
def get_inventory_alerts():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT * FROM inventory_alert')
            alerts: List[Dict[str, Any]] = cursor.fetchall() or []
        return jsonify(alerts)
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


@app.route('/api/dashboard/stats', methods=['GET'])
def get_dashboard_stats():
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            cursor.execute('SELECT COUNT(*) as total FROM textbooks')
            textbook_count_row = cursor.fetchone() or {'total': 0}
            textbook_count = int(textbook_count_row.get('total', 0))

            cursor.execute('SELECT COUNT(*) as total FROM students')
            student_count_row = cursor.fetchone() or {'total': 0}
            student_count = int(student_count_row.get('total', 0))

            cursor.execute('SELECT COUNT(*) as total FROM orders WHERE status = "pending"')
            pending_orders_row = cursor.fetchone() or {'total': 0}
            pending_orders = int(pending_orders_row.get('total', 0))

            cursor.execute('SELECT SUM(total_amount) as total FROM orders WHERE status = "pending"')
            pending_amount_result = cursor.fetchone() or {'total': 0}
            pending_amount = float(pending_amount_result.get('total') or 0)

            current_month = datetime.now().strftime('%Y-%m')
            cursor.execute('''
                SELECT SUM(payment_amount) as total 
                FROM payments 
                WHERE DATE_FORMAT(payment_date, "%%Y-%%m") = %s
            ''', (current_month,))
            monthly_payment_result = cursor.fetchone() or {'total': 0}
            monthly_payment = float(monthly_payment_result.get('total') or 0)

            cursor.execute('SELECT COUNT(*) as total FROM inventory_alert')
            low_stock_row = cursor.fetchone() or {'total': 0}
            low_stock_count = int(low_stock_row.get('total', 0))

            return jsonify({
                'textbook_count': textbook_count,
                'student_count': student_count,
                'pending_orders': pending_orders,
                'pending_amount': float(pending_amount),
                'monthly_payment': float(monthly_payment),
                'low_stock_count': low_stock_count
            })
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 审计日志API ============
@app.route('/api/audit-logs', methods=['GET'])
def get_audit_logs():
    conn = get_db_connection()
    try:
        page = request.args.get('page', 1, type=int)
        per_page = request.args.get('per_page', 50, type=int)
        offset = (page - 1) * per_page

        with conn.cursor() as cursor:
            cursor.execute('''
                SELECT * FROM audit_log 
                ORDER BY action_time DESC 
                LIMIT %s OFFSET %s
            ''', (per_page, offset))
            logs: List[Dict[str, Any]] = cursor.fetchall() or []

            for log in logs:
                if 'action_time' in log and log['action_time'] is not None:
                    log['action_time'] = format_date_str(log['action_time'])

            cursor.execute('SELECT COUNT(*) as total FROM audit_log')
            total_row = cursor.fetchone() or {'total': 0}
            total = int(total_row.get('total', 0))

            return jsonify({
                'logs': logs,
                'pagination': {
                    'page': page,
                    'per_page': per_page,
                    'total': total,
                    'total_pages': (total + per_page - 1) // per_page
                }
            })
    except Exception as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()


# ============ 系统状态检查API ============
@app.route('/api/system/health', methods=['GET'])
def system_health_check():
    try:
        conn = get_db_connection()
        with conn.cursor() as cursor:
            cursor.execute('SELECT 1 as status')
            db_status_row = cursor.fetchone() or {'status': 0}
            db_status = int(db_status_row.get('status', 0)) == 1

            cursor.execute('''
                SELECT COUNT(*) as count 
                FROM information_schema.tables 
                WHERE table_schema = 'order_book' 
                AND table_name IN ('textbooks', 'students', 'orders', 'payments', 'distributions')
            ''')
            table_count_row = cursor.fetchone() or {'count': 0}
            table_count = int(table_count_row.get('count', 0))

            cursor.execute('''
                SELECT COUNT(*) as count 
                FROM information_schema.views 
                WHERE table_schema = 'order_book'
            ''')
            view_count_row = cursor.fetchone() or {'count': 0}
            view_count = int(view_count_row.get('count', 0))

            return jsonify({
                'status': 'healthy',
                'database': 'connected' if db_status else 'disconnected',
                'tables_count': table_count,
                'views_count': view_count,
                'timestamp': datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            })
    except Exception as e:
        return jsonify({'status': 'unhealthy', 'error': str(e)}), 500
    finally:
        conn.close()


# ============ 启动应用 ============
if __name__ == '__main__':
    print("=" * 60)
    print("🚀 教材订购管理系统启动")
    print("📊 数据库: order_book (MySQL)")
    print("👤 用户: root")
    print("🌐 服务地址: http://127.0.0.1:5000")
    print("=" * 60)
    # 运行应用
    app.run(debug=True, host='127.0.0.1', port=5000)
